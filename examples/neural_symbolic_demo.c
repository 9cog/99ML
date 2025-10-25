/**
 * neural_symbolic_demo.c
 * 
 * Demonstration of the Neural-Symbolic Symbiosis
 * Shows how Scheme (mind) and ggml/C (brain) work together
 */

#include "neural_physics.h"
#include <stdio.h>
#include <stdlib.h>

// Forward declaration from bridge
void demonstrate_symbiosis();

int main(int argc, char** argv) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║   Genesis of Inference: Neural-Symbolic Symbiosis            ║\n");
    printf("║                                                               ║\n");
    printf("║   Mind (Scheme): Cognitive grammar, patterns, inference      ║\n");
    printf("║   Brain (ggml/C): Tensor operations, activation, attention   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    // Run the demonstration
    demonstrate_symbiosis();
    
    printf("\n=== Additional Neural Physics Examples ===\n\n");
    
    // Example 1: Tensor operations
    printf("Example 1: Matrix Multiplication\n");
    size_t shape_a[2] = {2, 3};
    size_t shape_b[2] = {3, 2};
    
    neural_tensor_t* A = neural_tensor_create(shape_a, 2);
    neural_tensor_t* B = neural_tensor_create(shape_b, 2);
    
    // Initialize A
    A->data[0] = 1.0f; A->data[1] = 2.0f; A->data[2] = 3.0f;
    A->data[3] = 4.0f; A->data[4] = 5.0f; A->data[5] = 6.0f;
    
    // Initialize B
    B->data[0] = 1.0f; B->data[1] = 2.0f;
    B->data[2] = 3.0f; B->data[3] = 4.0f;
    B->data[4] = 5.0f; B->data[5] = 6.0f;
    
    printf("Matrix A:\n");
    neural_tensor_print_info(A);
    printf("\nMatrix B:\n");
    neural_tensor_print_info(B);
    
    neural_tensor_t* C = neural_matmul(A, B);
    if (C) {
        printf("\nResult C = A × B:\n");
        neural_tensor_print_info(C);
        neural_tensor_free(C);
    }
    
    neural_tensor_free(A);
    neural_tensor_free(B);
    
    // Example 2: Activation functions
    printf("\n\nExample 2: Activation Functions\n");
    size_t shape_vec[1] = {5};
    neural_tensor_t* vec = neural_tensor_create(shape_vec, 1);
    
    vec->data[0] = -2.0f;
    vec->data[1] = -1.0f;
    vec->data[2] = 0.0f;
    vec->data[3] = 1.0f;
    vec->data[4] = 2.0f;
    
    printf("Input vector:\n");
    neural_tensor_print_info(vec);
    
    neural_tensor_t* relu_out = neural_relu(vec);
    if (relu_out) {
        printf("\nAfter ReLU:\n");
        neural_tensor_print_info(relu_out);
        neural_tensor_free(relu_out);
    }
    
    neural_tensor_t* tanh_out = neural_tanh(vec);
    if (tanh_out) {
        printf("\nAfter Tanh:\n");
        neural_tensor_print_info(tanh_out);
        neural_tensor_free(tanh_out);
    }
    
    neural_tensor_t* softmax_out = neural_softmax(vec);
    if (softmax_out) {
        printf("\nAfter Softmax:\n");
        neural_tensor_print_info(softmax_out);
        neural_tensor_free(softmax_out);
    }
    
    neural_tensor_free(vec);
    
    // Example 3: Attention mechanism
    printf("\n\nExample 3: Self-Attention\n");
    size_t shape_input[2] = {4, 8};
    neural_tensor_t* input = neural_tensor_create(shape_input, 2);
    
    // Initialize with sample data
    for (size_t i = 0; i < input->total_size; i++) {
        input->data[i] = (float)(i % 10) / 10.0f;
    }
    
    printf("Input sequence:\n");
    neural_tensor_print_info(input);
    
    neural_tensor_t* attended = attention_self(input, 2);
    if (attended) {
        printf("\nAfter self-attention:\n");
        neural_tensor_print_info(attended);
        neural_tensor_free(attended);
    }
    
    neural_tensor_free(input);
    
    // Example 4: Cognitive Context
    printf("\n\nExample 4: Cognitive Context with Activation Landscape\n");
    cognitive_context_t* context = cognitive_context_create(8, 64);
    
    if (context) {
        printf("Cognitive context created.\n");
        printf("  Nodes: 8\n");
        printf("  Working memory capacity: 64\n\n");
        
        // Set initial activations
        float activations[8] = {0.1f, 0.3f, 0.8f, 0.2f, 0.9f, 0.4f, 0.6f, 0.7f};
        activation_landscape_update(context->landscape, activations);
        
        printf("Initial activation landscape:\n");
        neural_tensor_print_info(context->landscape->activations);
        
        // Get active nodes
        size_t n_active = 0;
        size_t* active_nodes = activation_landscape_get_active_nodes(context->landscape, &n_active);
        
        if (active_nodes) {
            printf("\nActive nodes (above threshold 0.5): ");
            for (size_t i = 0; i < n_active; i++) {
                printf("%zu ", active_nodes[i]);
            }
            printf("\n");
            free(active_nodes);
        }
        
        cognitive_context_free(context);
    }
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                    Demonstration Complete                     ║\n");
    printf("║                                                               ║\n");
    printf("║  The neural-symbolic symbiosis enables:                      ║\n");
    printf("║  • Symbolic reasoning with neural grounding                  ║\n");
    printf("║  • Continuous activation landscapes                          ║\n");
    printf("║  • Attention-based information flow                          ║\n");
    printf("║  • Unified mind-brain architecture                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
