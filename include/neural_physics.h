/**
 * neural_physics.h
 * 
 * Neural Physics Layer - The Brain
 * Implements tensor operations, activation landscapes, and attention mechanisms
 * using ggml for the underlying computational substrate.
 */

#ifndef NEURAL_PHYSICS_H
#define NEURAL_PHYSICS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// CORE STRUCTURES
// ============================================================================

/**
 * Tensor representation for neural computations
 */
typedef struct {
    float* data;
    size_t* shape;
    size_t n_dims;
    size_t total_size;
} neural_tensor_t;

/**
 * Activation landscape - represents the state of neural activation
 */
typedef struct {
    neural_tensor_t* activations;
    float* thresholds;
    size_t n_nodes;
} activation_landscape_t;

/**
 * Attention mechanism state
 */
typedef struct {
    neural_tensor_t* attention_weights;
    neural_tensor_t* query;
    neural_tensor_t* key;
    neural_tensor_t* value;
    size_t n_heads;
} attention_state_t;

/**
 * Cognitive context - holds the complete neural state
 */
typedef struct {
    activation_landscape_t* landscape;
    attention_state_t* attention;
    neural_tensor_t* working_memory;
    size_t capacity;
} cognitive_context_t;

// ============================================================================
// TENSOR OPERATIONS
// ============================================================================

/**
 * Create a new tensor with given shape
 */
neural_tensor_t* neural_tensor_create(const size_t* shape, size_t n_dims);

/**
 * Free tensor memory
 */
void neural_tensor_free(neural_tensor_t* tensor);

/**
 * Matrix multiplication: C = A * B
 */
neural_tensor_t* neural_matmul(const neural_tensor_t* A, const neural_tensor_t* B);

/**
 * Element-wise operations
 */
neural_tensor_t* neural_add(const neural_tensor_t* A, const neural_tensor_t* B);
neural_tensor_t* neural_mul(const neural_tensor_t* A, const neural_tensor_t* B);

/**
 * Activation functions
 */
neural_tensor_t* neural_relu(const neural_tensor_t* input);
neural_tensor_t* neural_softmax(const neural_tensor_t* input);
neural_tensor_t* neural_tanh(const neural_tensor_t* input);

// ============================================================================
// ACTIVATION LANDSCAPE
// ============================================================================

/**
 * Create an activation landscape
 */
activation_landscape_t* activation_landscape_create(size_t n_nodes);

/**
 * Free activation landscape
 */
void activation_landscape_free(activation_landscape_t* landscape);

/**
 * Update activation values
 */
void activation_landscape_update(activation_landscape_t* landscape,
                                const float* new_activations);

/**
 * Spread activation through the landscape
 */
void activation_landscape_spread(activation_landscape_t* landscape,
                                const neural_tensor_t* connectivity,
                                float decay_factor);

/**
 * Get nodes above threshold
 */
size_t* activation_landscape_get_active_nodes(const activation_landscape_t* landscape,
                                              size_t* n_active);

// ============================================================================
// ATTENTION MECHANISMS
// ============================================================================

/**
 * Create attention state
 */
attention_state_t* attention_create(size_t n_heads, size_t dim_model, size_t dim_key);

/**
 * Free attention state
 */
void attention_free(attention_state_t* attention);

/**
 * Compute scaled dot-product attention
 */
neural_tensor_t* attention_compute(const attention_state_t* state,
                                  const neural_tensor_t* query,
                                  const neural_tensor_t* key,
                                  const neural_tensor_t* value);

/**
 * Multi-head attention
 */
neural_tensor_t* attention_multihead(const attention_state_t* state,
                                    const neural_tensor_t* input);

/**
 * Self-attention mechanism
 */
neural_tensor_t* attention_self(const neural_tensor_t* input, size_t n_heads);

// ============================================================================
// COGNITIVE CONTEXT
// ============================================================================

/**
 * Create a cognitive context
 */
cognitive_context_t* cognitive_context_create(size_t n_nodes, size_t memory_capacity);

/**
 * Free cognitive context
 */
void cognitive_context_free(cognitive_context_t* context);

/**
 * Update the cognitive state
 */
void cognitive_context_step(cognitive_context_t* context,
                           const neural_tensor_t* input);

/**
 * Get the current state vector
 */
neural_tensor_t* cognitive_context_get_state(const cognitive_context_t* context);

// ============================================================================
// NEURAL-SYMBOLIC BRIDGE
// ============================================================================

/**
 * Encode symbolic representation to neural tensor
 */
neural_tensor_t* encode_symbolic(const char* symbolic_repr);

/**
 * Decode neural tensor to symbolic representation
 */
char* decode_neural(const neural_tensor_t* tensor);

/**
 * Execute neural computation from symbolic specification
 */
neural_tensor_t* neural_execute(const char* operation,
                               const neural_tensor_t** inputs,
                               size_t n_inputs);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * Print tensor information
 */
void neural_tensor_print_info(const neural_tensor_t* tensor);

/**
 * Get tensor element
 */
float neural_tensor_get(const neural_tensor_t* tensor, const size_t* indices);

/**
 * Set tensor element
 */
void neural_tensor_set(neural_tensor_t* tensor, const size_t* indices, float value);

#ifdef __cplusplus
}
#endif

#endif // NEURAL_PHYSICS_H
