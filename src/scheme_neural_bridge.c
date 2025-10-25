/**
 * scheme_neural_bridge.c
 * 
 * Bridge between Scheme cognitive layer and C neural physics layer
 * Enables neural-symbolic symbiosis
 */

#include "neural_physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// SYMBOLIC-NEURAL CONVERSION
// ============================================================================

/**
 * Convert Scheme list to neural tensor
 * Format: "(tensor (shape d1 d2 ...) (data v1 v2 ...))"
 */
neural_tensor_t* scheme_list_to_tensor(const char* scheme_list) {
    // Simplified parser - in real implementation, use proper Scheme parser
    // This is a placeholder for demonstration
    
    size_t shape[2] = {2, 2};
    neural_tensor_t* tensor = neural_tensor_create(shape, 2);
    
    if (tensor) {
        // Initialize with sample data
        tensor->data[0] = 0.5f;
        tensor->data[1] = 0.3f;
        tensor->data[2] = 0.7f;
        tensor->data[3] = 0.9f;
    }
    
    return tensor;
}

/**
 * Convert neural tensor to Scheme list representation
 */
char* tensor_to_scheme_list(const neural_tensor_t* tensor) {
    if (!tensor) return NULL;
    
    // Allocate buffer for Scheme representation
    size_t buffer_size = 1024 + tensor->total_size * 20;
    char* result = (char*)malloc(buffer_size);
    if (!result) return NULL;
    
    // Build shape part
    char shape_str[256];
    int offset = sprintf(shape_str, "(shape");
    for (size_t i = 0; i < tensor->n_dims; i++) {
        offset += sprintf(shape_str + offset, " %zu", tensor->shape[i]);
    }
    sprintf(shape_str + offset, ")");
    
    // Build data part
    char data_str[1024];
    offset = sprintf(data_str, "(data");
    size_t n_print = (tensor->total_size < 100) ? tensor->total_size : 100;
    for (size_t i = 0; i < n_print; i++) {
        offset += sprintf(data_str + offset, " %.4f", tensor->data[i]);
    }
    sprintf(data_str + offset, ")");
    
    // Combine
    sprintf(result, "(tensor %s %s)", shape_str, data_str);
    
    return result;
}

// ============================================================================
// SCHEME CALLABLE FUNCTIONS
// ============================================================================

/**
 * Create a cognitive context from Scheme
 */
cognitive_context_t* scheme_create_context(size_t n_nodes, size_t memory_capacity) {
    return cognitive_context_create(n_nodes, memory_capacity);
}

/**
 * Execute neural operation from Scheme command
 */
char* scheme_neural_compute(const char* operation, const char** symbolic_inputs, size_t n_inputs) {
    if (!operation || !symbolic_inputs) return NULL;
    
    // Convert symbolic inputs to tensors
    neural_tensor_t** tensors = (neural_tensor_t**)malloc(n_inputs * sizeof(neural_tensor_t*));
    if (!tensors) return NULL;
    
    for (size_t i = 0; i < n_inputs; i++) {
        tensors[i] = scheme_list_to_tensor(symbolic_inputs[i]);
        if (!tensors[i]) {
            // Cleanup on error
            for (size_t j = 0; j < i; j++) {
                neural_tensor_free(tensors[j]);
            }
            free(tensors);
            return NULL;
        }
    }
    
    // Execute neural operation
    neural_tensor_t* result = neural_execute(operation, (const neural_tensor_t**)tensors, n_inputs);
    
    // Cleanup input tensors
    for (size_t i = 0; i < n_inputs; i++) {
        neural_tensor_free(tensors[i]);
    }
    free(tensors);
    
    // Convert result to Scheme representation
    char* scheme_result = NULL;
    if (result) {
        scheme_result = tensor_to_scheme_list(result);
        neural_tensor_free(result);
    }
    
    return scheme_result;
}

/**
 * Spread activation from Scheme
 */
void scheme_spread_activation(cognitive_context_t* context, float decay_factor) {
    if (!context) return;
    
    // Create simple connectivity matrix
    size_t n = context->landscape->n_nodes;
    size_t shape[2] = {n, n};
    neural_tensor_t* connectivity = neural_tensor_create(shape, 2);
    
    if (connectivity) {
        // Initialize with random small weights
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                connectivity->data[i * n + j] = (i != j) ? 0.1f : 0.9f;
            }
        }
        
        activation_landscape_spread(context->landscape, connectivity, decay_factor);
        neural_tensor_free(connectivity);
    }
}

/**
 * Get active concepts from activation landscape
 */
char* scheme_get_active_concepts(cognitive_context_t* context) {
    if (!context) return NULL;
    
    size_t n_active = 0;
    size_t* active_nodes = activation_landscape_get_active_nodes(context->landscape, &n_active);
    
    if (!active_nodes) return strdup("()");
    
    // Build Scheme list
    char* result = (char*)malloc(1024);
    int offset = sprintf(result, "(active-concepts");
    
    for (size_t i = 0; i < n_active && offset < 1000; i++) {
        offset += sprintf(result + offset, " %zu", active_nodes[i]);
    }
    sprintf(result + offset, ")");
    
    free(active_nodes);
    return result;
}

/**
 * Apply attention mechanism from Scheme
 */
char* scheme_apply_attention(cognitive_context_t* context, const char* input_repr) {
    if (!context || !input_repr) return NULL;
    
    neural_tensor_t* input = scheme_list_to_tensor(input_repr);
    if (!input) return NULL;
    
    neural_tensor_t* output = attention_multihead(context->attention, input);
    
    neural_tensor_free(input);
    
    if (!output) return NULL;
    
    char* result = tensor_to_scheme_list(output);
    neural_tensor_free(output);
    
    return result;
}

// ============================================================================
// MAIN BRIDGE INTERFACE
// ============================================================================

/**
 * Initialize the neural-symbolic bridge
 */
int bridge_init() {
    printf("Neural-Symbolic Bridge initialized.\n");
    printf("  Scheme (Mind) <-> C/ggml (Brain)\n");
    return 0;
}

/**
 * Shutdown the bridge
 */
void bridge_shutdown() {
    printf("Neural-Symbolic Bridge shutdown.\n");
}

/**
 * Process a Scheme command with neural backing
 */
char* bridge_process(const char* scheme_command) {
    if (!scheme_command) return NULL;
    
    // Parse and execute command
    // This is a simplified demonstration
    
    if (strstr(scheme_command, "neural-compute")) {
        // Example: (neural-compute 'add tensor1 tensor2)
        return strdup("(result (tensor (shape 2 2) (data 1.0 1.0 1.0 1.0)))");
    }
    
    return strdup("(error unknown-command)");
}

// ============================================================================
// DEMONSTRATION FUNCTION
// ============================================================================

void demonstrate_symbiosis() {
    printf("\n=== Neural-Symbolic Symbiosis Demonstration ===\n\n");
    
    // Create cognitive context
    printf("1. Creating cognitive context...\n");
    cognitive_context_t* context = cognitive_context_create(10, 100);
    
    if (!context) {
        printf("   Failed to create context!\n");
        return;
    }
    printf("   Context created with 10 nodes and capacity 100.\n\n");
    
    // Set up some activation
    printf("2. Setting up activation landscape...\n");
    float activations[10] = {0.8f, 0.6f, 0.3f, 0.9f, 0.2f, 0.7f, 0.4f, 0.1f, 0.5f, 0.85f};
    activation_landscape_update(context->landscape, activations);
    printf("   Activation landscape initialized.\n\n");
    
    // Get active concepts
    printf("3. Querying active concepts (threshold = 0.5)...\n");
    char* active = scheme_get_active_concepts(context);
    if (active) {
        printf("   %s\n\n", active);
        free(active);
    }
    
    // Spread activation
    printf("4. Spreading activation (decay = 0.8)...\n");
    scheme_spread_activation(context, 0.8f);
    printf("   Activation spread complete.\n\n");
    
    // Create and process tensors
    printf("5. Creating neural tensors...\n");
    size_t shape[2] = {2, 3};
    neural_tensor_t* tensor = neural_tensor_create(shape, 2);
    
    if (tensor) {
        tensor->data[0] = 1.0f; tensor->data[1] = 2.0f; tensor->data[2] = 3.0f;
        tensor->data[3] = 4.0f; tensor->data[4] = 5.0f; tensor->data[5] = 6.0f;
        
        printf("   Tensor created:\n");
        neural_tensor_print_info(tensor);
        
        // Convert to Scheme
        char* scheme_repr = tensor_to_scheme_list(tensor);
        if (scheme_repr) {
            printf("\n   Scheme representation:\n   %s\n\n", scheme_repr);
            free(scheme_repr);
        }
        
        neural_tensor_free(tensor);
    }
    
    // Cleanup
    printf("6. Cleaning up...\n");
    cognitive_context_free(context);
    printf("   Demonstration complete.\n\n");
}
