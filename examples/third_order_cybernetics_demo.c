/**
 * third_order_cybernetics_demo.c
 * 
 * Demonstration of Eric Schwarz's Third-Order Cybernetics Model
 * Shows the holistic metamodel in action with three planes, six cycles,
 * and the spiral of self-organization.
 */

#include "third_order_cybernetics.h"
#include "neural_physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_header(void) {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║   THIRD-ORDER CYBERNETICS: Eric Schwarz's Metamodel          ║\n");
    printf("║                                                               ║\n");
    printf("║   A Holistic Framework for Self-Organizing Systems           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
}

void demonstrate_three_planes(void) {
    printf("=== DEMONSTRATION 1: Three Ontological Planes ===\n\n");
    printf("The three planes represent different aspects of reality:\n");
    printf("  • Physical Plane: Energy, matter, objects\n");
    printf("  • Information Plane: Relations, networks, patterns\n");
    printf("  • Existential Plane: Being, wholeness, autonomy\n\n");
    
    // Create individual planes
    physical_plane_t* physical = physical_plane_create(8);
    information_plane_t* information = information_plane_create(8);
    existential_plane_t* existential = existential_plane_create(16);
    
    printf("Initial state:\n");
    printf("  Physical entropy: %.3f\n", physical->entropy_level);
    printf("  Information complexity: %.3f\n", information->complexity);
    printf("  Existential autonomy: %.3f\n\n", existential->autonomy_level);
    
    // Evolve each plane
    printf("Evolving planes over 10 timesteps...\n\n");
    for (int i = 0; i < 10; i++) {
        physical_plane_update(physical, 0.1f);
        information_plane_update(information, 0.1f);
        existential_plane_update(existential, 0.1f);
    }
    
    printf("After evolution:\n");
    printf("  Physical entropy: %.3f\n", physical->entropy_level);
    printf("  Information complexity: %.3f\n", information->complexity);
    printf("  Existential autonomy: %.3f\n", existential->autonomy_level);
    printf("  Self-aware: %s\n\n", existential->self_aware ? "YES" : "NO");
    
    physical_plane_free(physical);
    information_plane_free(information);
    existential_plane_free(existential);
}

void demonstrate_six_cycles(void) {
    printf("\n=== DEMONSTRATION 2: Six Cycles of Viable Systems ===\n\n");
    printf("Three stabilizing cycles (enable persistence):\n");
    printf("  1. Vortices - Physical recycling of matter and energy\n");
    printf("  3. Homeostasis - Functional feedback loops\n");
    printf("  5. Self-Reference - Existential autonomy\n\n");
    printf("Three creative cycles (enable change):\n");
    printf("  2. Morphogenesis - Self-organization creating structures\n");
    printf("  4. Autopoiesis - Self-production of living systems\n");
    printf("  6. Autogenesis - Self-creation leading to autonomy\n\n");
    
    cycle_state_t* cycles[6];
    for (int i = 0; i < 6; i++) {
        cycles[i] = cycle_create((cycle_type_t)(i + 1), 8);
    }
    
    printf("Initial cycle states:\n");
    for (int i = 0; i < 6; i++) {
        printf("  Cycle %d (%s): Activity=%.3f, %s\n",
               i + 1,
               cycle_is_stabilizing(cycles[i]->type) ? "stabilizing" : "creative",
               cycles[i]->activity_level,
               cycles[i]->is_active ? "active" : "inactive");
    }
    
    printf("\nEvolving cycles over 5 timesteps...\n");
    for (int t = 0; t < 5; t++) {
        for (int i = 0; i < 6; i++) {
            cycle_update(cycles[i], 0.2f);
        }
    }
    
    printf("\nFinal cycle states:\n");
    for (int i = 0; i < 6; i++) {
        printf("  Cycle %d: Activity=%.3f, Stability=%.3f\n",
               i + 1,
               cycles[i]->activity_level,
               cycles[i]->stability);
    }
    
    for (int i = 0; i < 6; i++) {
        cycle_free(cycles[i]);
    }
}

void demonstrate_spiral_evolution(void) {
    printf("\n\n=== DEMONSTRATION 3: Spiral of Self-Organization ===\n\n");
    printf("The seven phases of system evolution:\n");
    printf("  0. Entropic Drift - Far from equilibrium conditions\n");
    printf("  1. Morphogenesis - Differentiation via positive feedback\n");
    printf("  2. Communication - Fluxes establishing networks\n");
    printf("  3. Cybernetics - Causal networks influencing development\n");
    printf("  4. Autopoiesis - Self-productive cycle emergence\n");
    printf("  5. Self-Reference - Recursivity, machine and image converge\n");
    printf("  6. Autonomy - System actualization by own rules\n\n");
    
    spiral_state_t* spiral = spiral_create();
    
    printf("Tracing spiral evolution:\n");
    for (int i = 0; i < 15; i++) {
        printf("  Step %2d: Phase %d (%s) - %.0f%% complete\n",
               i,
               (int)spiral->current_phase,
               spiral_phase_name(spiral->current_phase),
               spiral->phase_completion * 100.0f);
        
        spiral_advance(spiral, 0.2f);
    }
    
    printf("\nSpiral has completed %zu full cycle(s)\n", spiral->cycle_count);
    
    spiral_free(spiral);
}

void demonstrate_complete_system(void) {
    printf("\n\n=== DEMONSTRATION 4: Complete Cybernetic System ===\n\n");
    printf("Creating an integrated third-order cybernetic system...\n");
    
    cybernetic_system_t* system = cybernetic_system_create(10, 20);
    if (!system) {
        printf("Failed to create system!\n");
        return;
    }
    
    printf("System created successfully.\n\n");
    
    // Show initial state
    cybernetic_system_print_state(system);
    
    // Evolve the system
    printf("\n\n=== EVOLVING SYSTEM OVER 20 TIMESTEPS ===\n");
    for (int i = 0; i < 20; i++) {
        cybernetic_system_step(system, 0.1f);
        
        if (i == 4 || i == 9 || i == 19) {
            printf("\n--- After %d timesteps ---\n", i + 1);
            printf("Viability: %.3f, Autonomy: %.3f, Phase: %s\n",
                   system->viability,
                   system->existential->autonomy_level,
                   spiral_phase_name(system->spiral->current_phase));
        }
    }
    
    // Show final state
    cybernetic_system_print_state(system);
    
    // Analyze the system
    cybernetic_system_analyze(system);
    
    cybernetic_system_free(system);
}

void demonstrate_leverage_points(void) {
    printf("\n\n=== DEMONSTRATION 5: Twelve Leverage Points ===\n\n");
    printf("System intervention points ordered by effectiveness:\n\n");
    
    printf("Physical Plane (Low Leverage):\n");
    for (int i = 1; i <= 3; i++) {
        printf("  %2d. %s (effectiveness: %.2f)\n",
               i,
               leverage_point_name((leverage_point_t)i),
               leverage_point_effectiveness((leverage_point_t)i));
    }
    
    printf("\nInformation Plane (Medium Leverage):\n");
    for (int i = 4; i <= 7; i++) {
        printf("  %2d. %s (effectiveness: %.2f)\n",
               i,
               leverage_point_name((leverage_point_t)i),
               leverage_point_effectiveness((leverage_point_t)i));
    }
    
    printf("\nExistential Plane (High Leverage):\n");
    for (int i = 8; i <= 12; i++) {
        printf("  %2d. %s (effectiveness: %.2f)\n",
               i,
               leverage_point_name((leverage_point_t)i),
               leverage_point_effectiveness((leverage_point_t)i));
    }
    
    // Demonstrate intervention
    printf("\n\nDemonstrating intervention effects:\n");
    cybernetic_system_t* system = cybernetic_system_create(8, 16);
    
    printf("\nInitial viability: %.3f\n", system->viability);
    
    // Low leverage intervention
    printf("\nApplying LOW leverage intervention (Constants)...\n");
    cybernetic_system_intervene(system, LEVERAGE_CONSTANTS, 0.5f);
    cybernetic_system_step(system, 0.1f);
    printf("  New viability: %.3f (change: %.3f)\n",
           system->viability,
           system->viability - 0.5f);
    
    // High leverage intervention
    printf("\nApplying HIGH leverage intervention (Paradigms)...\n");
    float old_viability = system->viability;
    cybernetic_system_intervene(system, LEVERAGE_PARADIGMS, 0.5f);
    cybernetic_system_step(system, 0.1f);
    printf("  New viability: %.3f (change: %.3f)\n",
           system->viability,
           system->viability - old_viability);
    
    cybernetic_system_free(system);
}

void demonstrate_self_organization(void) {
    printf("\n\n=== DEMONSTRATION 6: Self-Organization Process ===\n\n");
    printf("Observing emergence of self-organizing behavior...\n\n");
    
    cybernetic_system_t* system = cybernetic_system_create(12, 24);
    
    printf("Initial state:\n");
    printf("  Viability: %.3f\n", system->viability);
    printf("  Self-organizing: %s\n", system->is_self_organizing ? "YES" : "NO");
    printf("  Autonomy: %.3f\n\n", system->existential->autonomy_level);
    
    // Trigger self-organization
    printf("Triggering self-organization process...\n");
    cybernetic_system_self_organize(system);
    
    // Evolve to see effects
    printf("\nEvolution after triggering:\n");
    for (int i = 0; i < 10; i++) {
        cybernetic_system_step(system, 0.15f);
        printf("  Step %2d: Viability=%.3f, Autonomy=%.3f, Phase=%s\n",
               i + 1,
               system->viability,
               system->existential->autonomy_level,
               spiral_phase_name(system->spiral->current_phase));
    }
    
    printf("\nFinal state:\n");
    printf("  Self-organizing: %s\n", system->is_self_organizing ? "YES" : "NO");
    printf("  Self-aware: %s\n", system->existential->self_aware ? "YES" : "NO");
    
    cybernetic_system_free(system);
}

void demonstrate_export(void) {
    printf("\n\n=== DEMONSTRATION 7: System State Export ===\n\n");
    printf("Exporting system state to symbolic representation...\n\n");
    
    cybernetic_system_t* system = cybernetic_system_create(6, 12);
    
    // Evolve a bit
    for (int i = 0; i < 5; i++) {
        cybernetic_system_step(system, 0.1f);
    }
    
    // Export to Scheme-like format
    char* export = cybernetic_system_export_state(system);
    if (export) {
        printf("Exported state:\n%s\n", export);
        free(export);
    }
    
    cybernetic_system_free(system);
}

void print_conclusion(void) {
    printf("\n\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DEMONSTRATION COMPLETE                     ║\n");
    printf("║                                                               ║\n");
    printf("║  Third-Order Cybernetics Key Insights:                       ║\n");
    printf("║                                                               ║\n");
    printf("║  • Reality has three interdependent planes                   ║\n");
    printf("║  • Viable systems need both stabilizing and creative cycles  ║\n");
    printf("║  • Self-organization follows a predictable spiral pattern    ║\n");
    printf("║  • Highest leverage points are at the existential plane      ║\n");
    printf("║  • Autonomy emerges from recursive self-reference            ║\n");
    printf("║                                                               ║\n");
    printf("║  This metamodel transcends mechanistic paradigms and         ║\n");
    printf("║  provides a holistic framework for understanding complex     ║\n");
    printf("║  adaptive systems across all domains.                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
}

int main(void) {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    print_header();
    
    demonstrate_three_planes();
    demonstrate_six_cycles();
    demonstrate_spiral_evolution();
    demonstrate_complete_system();
    demonstrate_leverage_points();
    demonstrate_self_organization();
    demonstrate_export();
    
    print_conclusion();
    
    return 0;
}
