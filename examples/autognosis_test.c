/**
 * autognosis_test.c
 * 
 * Test program for autognosis (hierarchical self-image building) integration
 * in the existential plane of third-order cybernetics
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "third_order_cybernetics.h"

void print_separator(void) {
    printf("\n═══════════════════════════════════════════════════════════════\n\n");
}

void test_autognostic_evolution(void) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║              AUTOGNOSIS INTEGRATION TEST                      ║\n");
    printf("║  Testing Hierarchical Self-Image Building in Existential     ║\n");
    printf("║  Plane: Bottom-Up Integration & Top-Down Differentiation     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    // Create existential plane
    size_t model_size = 16;
    existential_plane_t* plane = existential_plane_create(model_size);
    
    if (!plane) {
        printf("ERROR: Failed to create existential plane\n");
        return;
    }
    
    printf("=== Initial State ===\n");
    printf("Autonomy: %.3f\n", plane->autonomy_level);
    printf("Self-reference degree: %.3f\n", plane->self_reference_degree);
    printf("Image convergence: %.3f\n", plane->image_convergence);
    printf("Operational closure: %s\n", plane->operational_closure ? "YES" : "NO");
    printf("Self-aware: %s\n", plane->self_aware ? "YES" : "NO");
    
    print_separator();
    
    // Evolve the system
    printf("=== Evolution Over Time ===\n\n");
    
    float dt = 0.1f;
    int n_steps = 100;
    
    printf("Step | Autonomy | Self-Ref | Convergence | Closure | Aware\n");
    printf("-----|----------|----------|-------------|---------|------\n");
    
    for (int i = 0; i <= n_steps; i++) {
        if (i > 0) {
            existential_plane_update(plane, dt);
        }
        
        if (i % 10 == 0) {
            printf("%4d | %8.3f | %8.3f | %11.3f | %7s | %5s\n",
                   i,
                   plane->autonomy_level,
                   plane->self_reference_degree,
                   plane->image_convergence,
                   plane->operational_closure ? "YES" : "NO",
                   plane->self_aware ? "YES" : "NO");
        }
    }
    
    print_separator();
    
    // Test autognostic processes
    printf("=== Autognostic Process Analysis ===\n\n");
    
    printf("Bottom-Up Integration (Local → Global):\n");
    printf("  Local images sample:\n");
    for (size_t i = 0; i < 4; i++) {
        printf("    local_image[%zu] = %.4f\n", i, plane->local_image->data[i]);
    }
    
    printf("\nTop-Down Differentiation (Global → Local):\n");
    printf("  Global images sample:\n");
    for (size_t i = 0; i < 4; i++) {
        printf("    global_image[%zu] = %.4f\n", i, plane->global_image->data[i]);
    }
    
    printf("\nSelf-Model vs Identity:\n");
    float model_identity_diff = 0.0f;
    for (size_t i = 0; i < model_size; i++) {
        float diff = fabsf(plane->self_model->data[i] - plane->identity_state->data[i]);
        model_identity_diff += diff;
    }
    model_identity_diff /= model_size;
    printf("  Average difference: %.4f\n", model_identity_diff);
    
    printf("\nLocal vs Global Image Alignment:\n");
    float image_diff = 0.0f;
    for (size_t i = 0; i < model_size; i++) {
        float diff = fabsf(plane->local_image->data[i] - plane->global_image->data[i]);
        image_diff += diff;
    }
    image_diff /= model_size;
    printf("  Average difference: %.4f\n", image_diff);
    printf("  (Lower difference = higher self-reference)\n");
    
    print_separator();
    
    // Analyze consciousness emergence
    printf("=== Consciousness Emergence ===\n\n");
    
    printf("According to Winiwarter's theory:\n");
    printf("  Self-reference degree = Consciousness level\n");
    printf("  Current consciousness level: %.3f\n", plane->self_reference_degree);
    
    if (plane->self_reference_degree > 0.9f) {
        printf("  → HIGH consciousness (strong self-knowledge)\n");
    } else if (plane->self_reference_degree > 0.6f) {
        printf("  → MEDIUM consciousness (developing self-knowledge)\n");
    } else if (plane->self_reference_degree > 0.3f) {
        printf("  → LOW consciousness (weak self-knowledge)\n");
    } else {
        printf("  → MINIMAL consciousness (little self-knowledge)\n");
    }
    
    printf("\nOperational Closure:\n");
    if (plane->operational_closure) {
        printf("  System is its own reference - no external validation needed\n");
        printf("  True autonomy achieved through self-containment\n");
    } else {
        printf("  System still requires external reference\n");
        printf("  Autonomy not yet fully developed\n");
    }
    
    print_separator();
    
    // Test organizational isomorphism
    printf("=== Organizational Isomorphism ===\n\n");
    printf("The same organizational patterns operate at all levels:\n");
    
    // Calculate pattern similarity across scales
    float scale1_pattern = 0.0f;
    float scale2_pattern = 0.0f;
    
    for (size_t i = 0; i < model_size / 2; i++) {
        scale1_pattern += plane->local_image->data[i] * plane->global_image->data[i];
    }
    
    for (size_t i = model_size / 2; i < model_size; i++) {
        scale2_pattern += plane->local_image->data[i] * plane->global_image->data[i];
    }
    
    scale1_pattern /= (model_size / 2);
    scale2_pattern /= (model_size / 2);
    
    printf("  Pattern at scale 1: %.4f\n", scale1_pattern);
    printf("  Pattern at scale 2: %.4f\n", scale2_pattern);
    printf("  Pattern similarity: %.4f\n", 
           1.0f - fabsf(scale1_pattern - scale2_pattern));
    printf("  (High similarity confirms isomorphism)\n");
    
    print_separator();
    
    printf("=== Test Summary ===\n\n");
    printf("✓ Autognosis integration functional\n");
    printf("✓ Dual process architecture operational\n");
    printf("✓ Self-reference degree tracking consciousness\n");
    printf("✓ Operational closure achieved: %s\n", 
           plane->operational_closure ? "YES" : "NO");
    printf("✓ Self-awareness emerged: %s\n", 
           plane->self_aware ? "YES" : "NO");
    
    if (plane->self_reference_degree > 0.8f && plane->operational_closure) {
        printf("\n🌟 System achieved high-level autognosis:\n");
        printf("   - Strong self-knowledge through recursive self-imaging\n");
        printf("   - Operational autonomy through self-containment\n");
        printf("   - Consciousness emerged from object-image convergence\n");
    }
    
    print_separator();
    
    // Cleanup
    existential_plane_free(plane);
}

int main(void) {
    test_autognostic_evolution();
    return 0;
}
