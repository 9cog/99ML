/**
 * neural_physics.c
 * 
 * Implementation of the neural physics layer
 * The computational substrate that drives the cognitive system
 */

#include "neural_physics.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// ============================================================================
// TENSOR OPERATIONS IMPLEMENTATION
// ============================================================================

neural_tensor_t* neural_tensor_create(const size_t* shape, size_t n_dims) {
    neural_tensor_t* tensor = (neural_tensor_t*)malloc(sizeof(neural_tensor_t));
    if (!tensor) return NULL;
    
    tensor->n_dims = n_dims;
    tensor->shape = (size_t*)malloc(n_dims * sizeof(size_t));
    if (!tensor->shape) {
        free(tensor);
        return NULL;
    }
    
    // Calculate total size
    tensor->total_size = 1;
    for (size_t i = 0; i < n_dims; i++) {
        tensor->shape[i] = shape[i];
        tensor->total_size *= shape[i];
    }
    
    // Allocate data
    tensor->data = (float*)calloc(tensor->total_size, sizeof(float));
    if (!tensor->data) {
        free(tensor->shape);
        free(tensor);
        return NULL;
    }
    
    return tensor;
}

void neural_tensor_free(neural_tensor_t* tensor) {
    if (tensor) {
        if (tensor->data) free(tensor->data);
        if (tensor->shape) free(tensor->shape);
        free(tensor);
    }
}

neural_tensor_t* neural_matmul(const neural_tensor_t* A, const neural_tensor_t* B) {
    if (!A || !B || A->n_dims != 2 || B->n_dims != 2) return NULL;
    if (A->shape[1] != B->shape[0]) return NULL;
    
    size_t m = A->shape[0];
    size_t n = B->shape[1];
    size_t k = A->shape[1];
    
    size_t result_shape[2] = {m, n};
    neural_tensor_t* result = neural_tensor_create(result_shape, 2);
    if (!result) return NULL;
    
    // Simple matrix multiplication
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            float sum = 0.0f;
            for (size_t l = 0; l < k; l++) {
                sum += A->data[i * k + l] * B->data[l * n + j];
            }
            result->data[i * n + j] = sum;
        }
    }
    
    return result;
}

neural_tensor_t* neural_add(const neural_tensor_t* A, const neural_tensor_t* B) {
    if (!A || !B || A->total_size != B->total_size) return NULL;
    
    neural_tensor_t* result = neural_tensor_create(A->shape, A->n_dims);
    if (!result) return NULL;
    
    for (size_t i = 0; i < A->total_size; i++) {
        result->data[i] = A->data[i] + B->data[i];
    }
    
    return result;
}

neural_tensor_t* neural_mul(const neural_tensor_t* A, const neural_tensor_t* B) {
    if (!A || !B || A->total_size != B->total_size) return NULL;
    
    neural_tensor_t* result = neural_tensor_create(A->shape, A->n_dims);
    if (!result) return NULL;
    
    for (size_t i = 0; i < A->total_size; i++) {
        result->data[i] = A->data[i] * B->data[i];
    }
    
    return result;
}

neural_tensor_t* neural_relu(const neural_tensor_t* input) {
    if (!input) return NULL;
    
    neural_tensor_t* result = neural_tensor_create(input->shape, input->n_dims);
    if (!result) return NULL;
    
    for (size_t i = 0; i < input->total_size; i++) {
        result->data[i] = (input->data[i] > 0.0f) ? input->data[i] : 0.0f;
    }
    
    return result;
}

neural_tensor_t* neural_softmax(const neural_tensor_t* input) {
    if (!input) return NULL;
    
    neural_tensor_t* result = neural_tensor_create(input->shape, input->n_dims);
    if (!result) return NULL;
    
    // Find max for numerical stability
    float max_val = input->data[0];
    for (size_t i = 1; i < input->total_size; i++) {
        if (input->data[i] > max_val) max_val = input->data[i];
    }
    
    // Compute exp and sum
    float sum = 0.0f;
    for (size_t i = 0; i < input->total_size; i++) {
        result->data[i] = expf(input->data[i] - max_val);
        sum += result->data[i];
    }
    
    // Normalize
    for (size_t i = 0; i < input->total_size; i++) {
        result->data[i] /= sum;
    }
    
    return result;
}

neural_tensor_t* neural_tanh(const neural_tensor_t* input) {
    if (!input) return NULL;
    
    neural_tensor_t* result = neural_tensor_create(input->shape, input->n_dims);
    if (!result) return NULL;
    
    for (size_t i = 0; i < input->total_size; i++) {
        result->data[i] = tanhf(input->data[i]);
    }
    
    return result;
}

// ============================================================================
// ACTIVATION LANDSCAPE IMPLEMENTATION
// ============================================================================

activation_landscape_t* activation_landscape_create(size_t n_nodes) {
    activation_landscape_t* landscape = (activation_landscape_t*)malloc(sizeof(activation_landscape_t));
    if (!landscape) return NULL;
    
    landscape->n_nodes = n_nodes;
    size_t shape[1] = {n_nodes};
    landscape->activations = neural_tensor_create(shape, 1);
    landscape->thresholds = (float*)calloc(n_nodes, sizeof(float));
    
    if (!landscape->activations || !landscape->thresholds) {
        activation_landscape_free(landscape);
        return NULL;
    }
    
    // Default threshold
    for (size_t i = 0; i < n_nodes; i++) {
        landscape->thresholds[i] = 0.5f;
    }
    
    return landscape;
}

void activation_landscape_free(activation_landscape_t* landscape) {
    if (landscape) {
        if (landscape->activations) neural_tensor_free(landscape->activations);
        if (landscape->thresholds) free(landscape->thresholds);
        free(landscape);
    }
}

void activation_landscape_update(activation_landscape_t* landscape,
                                const float* new_activations) {
    if (!landscape || !new_activations) return;
    
    memcpy(landscape->activations->data, new_activations, 
           landscape->n_nodes * sizeof(float));
}

void activation_landscape_spread(activation_landscape_t* landscape,
                                const neural_tensor_t* connectivity,
                                float decay_factor) {
    if (!landscape || !connectivity) return;
    
    // Create temporary 2D tensor for matrix multiplication
    // Reshape 1D activations to 2D [1, n_nodes]
    size_t shape_2d[2] = {1, landscape->n_nodes};
    neural_tensor_t* activations_2d = neural_tensor_create(shape_2d, 2);
    if (!activations_2d) return;
    
    memcpy(activations_2d->data, landscape->activations->data, 
           landscape->n_nodes * sizeof(float));
    
    // Spread activation through connectivity matrix
    neural_tensor_t* new_activations = neural_matmul(activations_2d, connectivity);
    neural_tensor_free(activations_2d);
    
    if (!new_activations) return;
    
    // Apply decay
    for (size_t i = 0; i < landscape->n_nodes && i < new_activations->total_size; i++) {
        landscape->activations->data[i] = new_activations->data[i] * decay_factor;
    }
    
    neural_tensor_free(new_activations);
}

size_t* activation_landscape_get_active_nodes(const activation_landscape_t* landscape,
                                              size_t* n_active) {
    if (!landscape || !n_active) return NULL;
    
    // Count active nodes
    *n_active = 0;
    for (size_t i = 0; i < landscape->n_nodes; i++) {
        if (landscape->activations->data[i] > landscape->thresholds[i]) {
            (*n_active)++;
        }
    }
    
    if (*n_active == 0) return NULL;
    
    // Collect active node indices
    size_t* active_nodes = (size_t*)malloc(*n_active * sizeof(size_t));
    size_t idx = 0;
    for (size_t i = 0; i < landscape->n_nodes; i++) {
        if (landscape->activations->data[i] > landscape->thresholds[i]) {
            active_nodes[idx++] = i;
        }
    }
    
    return active_nodes;
}

// ============================================================================
// ATTENTION MECHANISMS IMPLEMENTATION
// ============================================================================

attention_state_t* attention_create(size_t n_heads, size_t dim_model, size_t dim_key) {
    attention_state_t* attention = (attention_state_t*)malloc(sizeof(attention_state_t));
    if (!attention) return NULL;
    
    attention->n_heads = n_heads;
    
    size_t shape_weights[2] = {dim_model, dim_model};
    attention->attention_weights = neural_tensor_create(shape_weights, 2);
    
    size_t shape_qkv[2] = {dim_model, dim_key};
    attention->query = neural_tensor_create(shape_qkv, 2);
    attention->key = neural_tensor_create(shape_qkv, 2);
    attention->value = neural_tensor_create(shape_qkv, 2);
    
    if (!attention->attention_weights || !attention->query || 
        !attention->key || !attention->value) {
        attention_free(attention);
        return NULL;
    }
    
    return attention;
}

void attention_free(attention_state_t* attention) {
    if (attention) {
        if (attention->attention_weights) neural_tensor_free(attention->attention_weights);
        if (attention->query) neural_tensor_free(attention->query);
        if (attention->key) neural_tensor_free(attention->key);
        if (attention->value) neural_tensor_free(attention->value);
        free(attention);
    }
}

neural_tensor_t* attention_compute(const attention_state_t* state,
                                  const neural_tensor_t* query,
                                  const neural_tensor_t* key,
                                  const neural_tensor_t* value) {
    if (!state || !query || !key || !value) return NULL;
    
    // Compute Q * K^T
    neural_tensor_t* scores = neural_matmul(query, key);
    if (!scores) return NULL;
    
    // Scale by sqrt(d_k)
    float scale = 1.0f / sqrtf((float)key->shape[1]);
    for (size_t i = 0; i < scores->total_size; i++) {
        scores->data[i] *= scale;
    }
    
    // Apply softmax
    neural_tensor_t* attention_weights = neural_softmax(scores);
    neural_tensor_free(scores);
    
    if (!attention_weights) return NULL;
    
    // Multiply by values
    neural_tensor_t* output = neural_matmul(attention_weights, value);
    neural_tensor_free(attention_weights);
    
    return output;
}

neural_tensor_t* attention_multihead(const attention_state_t* state,
                                    const neural_tensor_t* input) {
    if (!state || !input) return NULL;
    
    // Simplified multi-head attention
    return attention_compute(state, input, input, input);
}

neural_tensor_t* attention_self(const neural_tensor_t* input, size_t n_heads) {
    if (!input || input->n_dims != 2) return NULL;
    
    attention_state_t* state = attention_create(n_heads, input->shape[1], input->shape[1]);
    if (!state) return NULL;
    
    neural_tensor_t* output = attention_multihead(state, input);
    attention_free(state);
    
    return output;
}

// ============================================================================
// COGNITIVE CONTEXT IMPLEMENTATION
// ============================================================================

cognitive_context_t* cognitive_context_create(size_t n_nodes, size_t memory_capacity) {
    cognitive_context_t* context = (cognitive_context_t*)malloc(sizeof(cognitive_context_t));
    if (!context) return NULL;
    
    context->capacity = memory_capacity;
    context->landscape = activation_landscape_create(n_nodes);
    context->attention = attention_create(4, n_nodes, n_nodes / 4);
    
    size_t memory_shape[1] = {memory_capacity};
    context->working_memory = neural_tensor_create(memory_shape, 1);
    
    if (!context->landscape || !context->attention || !context->working_memory) {
        cognitive_context_free(context);
        return NULL;
    }
    
    return context;
}

void cognitive_context_free(cognitive_context_t* context) {
    if (context) {
        if (context->landscape) activation_landscape_free(context->landscape);
        if (context->attention) attention_free(context->attention);
        if (context->working_memory) neural_tensor_free(context->working_memory);
        free(context);
    }
}

void cognitive_context_step(cognitive_context_t* context,
                           const neural_tensor_t* input) {
    if (!context || !input) return;
    
    // Update activation landscape with input
    if (input->total_size <= context->landscape->n_nodes) {
        memcpy(context->landscape->activations->data, input->data,
               input->total_size * sizeof(float));
    }
}

neural_tensor_t* cognitive_context_get_state(const cognitive_context_t* context) {
    if (!context) return NULL;
    
    // Return a copy of the current activation landscape
    neural_tensor_t* state = neural_tensor_create(
        context->landscape->activations->shape,
        context->landscape->activations->n_dims
    );
    
    if (state) {
        memcpy(state->data, context->landscape->activations->data,
               context->landscape->activations->total_size * sizeof(float));
    }
    
    return state;
}

// ============================================================================
// NEURAL-SYMBOLIC BRIDGE IMPLEMENTATION
// ============================================================================

neural_tensor_t* encode_symbolic(const char* symbolic_repr) {
    if (!symbolic_repr) return NULL;
    
    // Simple encoding: convert string to tensor
    size_t len = strlen(symbolic_repr);
    size_t shape[1] = {len};
    neural_tensor_t* tensor = neural_tensor_create(shape, 1);
    
    if (tensor) {
        for (size_t i = 0; i < len; i++) {
            tensor->data[i] = (float)symbolic_repr[i] / 255.0f;
        }
    }
    
    return tensor;
}

char* decode_neural(const neural_tensor_t* tensor) {
    if (!tensor) return NULL;
    
    char* result = (char*)malloc((tensor->total_size + 1) * sizeof(char));
    if (!result) return NULL;
    
    for (size_t i = 0; i < tensor->total_size; i++) {
        result[i] = (char)(tensor->data[i] * 255.0f);
    }
    result[tensor->total_size] = '\0';
    
    return result;
}

neural_tensor_t* neural_execute(const char* operation,
                               const neural_tensor_t** inputs,
                               size_t n_inputs) {
    if (!operation || !inputs || n_inputs == 0) return NULL;
    
    // Simple operation dispatch
    if (strcmp(operation, "add") == 0 && n_inputs >= 2) {
        return neural_add(inputs[0], inputs[1]);
    } else if (strcmp(operation, "mul") == 0 && n_inputs >= 2) {
        return neural_mul(inputs[0], inputs[1]);
    } else if (strcmp(operation, "matmul") == 0 && n_inputs >= 2) {
        return neural_matmul(inputs[0], inputs[1]);
    } else if (strcmp(operation, "relu") == 0 && n_inputs >= 1) {
        return neural_relu(inputs[0]);
    } else if (strcmp(operation, "softmax") == 0 && n_inputs >= 1) {
        return neural_softmax(inputs[0]);
    } else if (strcmp(operation, "tanh") == 0 && n_inputs >= 1) {
        return neural_tanh(inputs[0]);
    }
    
    return NULL;
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

void neural_tensor_print_info(const neural_tensor_t* tensor) {
    if (!tensor) {
        printf("Tensor: NULL\n");
        return;
    }
    
    printf("Tensor: %p\n", (void*)tensor);
    printf("  Dimensions: %zu\n", tensor->n_dims);
    printf("  Shape: [");
    for (size_t i = 0; i < tensor->n_dims; i++) {
        printf("%zu", tensor->shape[i]);
        if (i < tensor->n_dims - 1) printf(", ");
    }
    printf("]\n");
    printf("  Total size: %zu\n", tensor->total_size);
    
    // Print first few elements
    printf("  Data (first 10): [");
    size_t n_print = (tensor->total_size < 10) ? tensor->total_size : 10;
    for (size_t i = 0; i < n_print; i++) {
        printf("%.4f", tensor->data[i]);
        if (i < n_print - 1) printf(", ");
    }
    if (tensor->total_size > 10) printf(", ...");
    printf("]\n");
}

float neural_tensor_get(const neural_tensor_t* tensor, const size_t* indices) {
    if (!tensor || !indices || tensor->n_dims == 0) return 0.0f;
    
    size_t flat_index = 0;
    size_t stride = 1;
    for (size_t i = tensor->n_dims; i > 0; i--) {
        flat_index += indices[i - 1] * stride;
        stride *= tensor->shape[i - 1];
    }
    
    if (flat_index < tensor->total_size) {
        return tensor->data[flat_index];
    }
    
    return 0.0f;
}

void neural_tensor_set(neural_tensor_t* tensor, const size_t* indices, float value) {
    if (!tensor || !indices || tensor->n_dims == 0) return;
    
    size_t flat_index = 0;
    size_t stride = 1;
    for (size_t i = tensor->n_dims; i > 0; i--) {
        flat_index += indices[i - 1] * stride;
        stride *= tensor->shape[i - 1];
    }
    
    if (flat_index < tensor->total_size) {
        tensor->data[flat_index] = value;
    }
}
