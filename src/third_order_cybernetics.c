/**
 * third_order_cybernetics.c
 * 
 * Implementation of Eric Schwarz's third-order cybernetics model
 * A holistic metamodel for self-organizing systems
 */

#include "third_order_cybernetics.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// ============================================================================
// PLANE IMPLEMENTATIONS
// ============================================================================

physical_plane_t* physical_plane_create(size_t n_components) {
    physical_plane_t* plane = (physical_plane_t*)malloc(sizeof(physical_plane_t));
    if (!plane) return NULL;
    
    size_t shape[1] = {n_components};
    plane->energy_state = neural_tensor_create(shape, 1);
    plane->matter_structure = neural_tensor_create(shape, 1);
    
    if (!plane->energy_state || !plane->matter_structure) {
        physical_plane_free(plane);
        return NULL;
    }
    
    // Initialize with random energy distribution
    for (size_t i = 0; i < n_components; i++) {
        plane->energy_state->data[i] = (float)rand() / RAND_MAX;
        plane->matter_structure->data[i] = 1.0f;
    }
    
    plane->entropy_level = 0.5f;
    plane->n_components = n_components;
    
    return plane;
}

void physical_plane_free(physical_plane_t* plane) {
    if (plane) {
        neural_tensor_free(plane->energy_state);
        neural_tensor_free(plane->matter_structure);
        free(plane);
    }
}

void physical_plane_update(physical_plane_t* plane, float dt) {
    if (!plane || !plane->energy_state) return;
    
    // Vortex cycle: Energy recycling and metabolism
    // Apply decay and redistribution
    float total_energy = 0.0f;
    for (size_t i = 0; i < plane->n_components; i++) {
        total_energy += plane->energy_state->data[i];
    }
    
    // Redistribute with entropy increase
    float avg_energy = total_energy / plane->n_components;
    for (size_t i = 0; i < plane->n_components; i++) {
        float diff = avg_energy - plane->energy_state->data[i];
        plane->energy_state->data[i] += diff * dt * 0.1f;
    }
    
    // Update entropy
    float variance = 0.0f;
    for (size_t i = 0; i < plane->n_components; i++) {
        float diff = plane->energy_state->data[i] - avg_energy;
        variance += diff * diff;
    }
    plane->entropy_level = 0.5f + 0.5f * tanhf(variance / plane->n_components - 1.0f);
}

information_plane_t* information_plane_create(size_t n_relations) {
    information_plane_t* plane = (information_plane_t*)malloc(sizeof(information_plane_t));
    if (!plane) return NULL;
    
    size_t shape[2] = {n_relations, n_relations};
    plane->connectivity = neural_tensor_create(shape, 2);
    
    size_t flow_shape[1] = {n_relations};
    plane->information_flow = neural_tensor_create(flow_shape, 1);
    
    if (!plane->connectivity || !plane->information_flow) {
        information_plane_free(plane);
        return NULL;
    }
    
    // Initialize connectivity matrix
    for (size_t i = 0; i < n_relations; i++) {
        for (size_t j = 0; j < n_relations; j++) {
            float connection = (i != j && (float)rand() / RAND_MAX > 0.7f) ? 
                              (float)rand() / RAND_MAX : 0.0f;
            plane->connectivity->data[i * n_relations + j] = connection;
        }
        plane->information_flow->data[i] = 0.5f;
    }
    
    plane->complexity = (float)n_relations;
    plane->n_relations = n_relations;
    
    return plane;
}

void information_plane_free(information_plane_t* plane) {
    if (plane) {
        neural_tensor_free(plane->connectivity);
        neural_tensor_free(plane->information_flow);
        free(plane);
    }
}

void information_plane_update(information_plane_t* plane, float dt) {
    if (!plane || !plane->information_flow || !plane->connectivity) return;
    
    // Homeostatic cycle: Information flow regulation
    // Spread information through network
    float* new_flow = (float*)calloc(plane->n_relations, sizeof(float));
    if (!new_flow) return;
    
    for (size_t i = 0; i < plane->n_relations; i++) {
        float incoming = 0.0f;
        for (size_t j = 0; j < plane->n_relations; j++) {
            incoming += plane->connectivity->data[j * plane->n_relations + i] * 
                       plane->information_flow->data[j];
        }
        new_flow[i] = plane->information_flow->data[i] * (1.0f - dt) + incoming * dt;
    }
    
    // Update flow with homeostatic regulation
    for (size_t i = 0; i < plane->n_relations; i++) {
        plane->information_flow->data[i] = new_flow[i];
        // Apply bounds
        if (plane->information_flow->data[i] > 1.0f) {
            plane->information_flow->data[i] = 1.0f;
        }
        if (plane->information_flow->data[i] < 0.0f) {
            plane->information_flow->data[i] = 0.0f;
        }
    }
    
    free(new_flow);
    
    // Update complexity measure
    float sum_connections = 0.0f;
    for (size_t i = 0; i < plane->n_relations * plane->n_relations; i++) {
        sum_connections += fabsf(plane->connectivity->data[i]);
    }
    plane->complexity = sum_connections / plane->n_relations;
}

existential_plane_t* existential_plane_create(size_t model_size) {
    existential_plane_t* plane = (existential_plane_t*)malloc(sizeof(existential_plane_t));
    if (!plane) return NULL;
    
    size_t shape[1] = {model_size};
    plane->self_model = neural_tensor_create(shape, 1);
    plane->identity_state = neural_tensor_create(shape, 1);
    
    // Autognosis: hierarchical self-image building
    plane->local_image = neural_tensor_create(shape, 1);
    plane->global_image = neural_tensor_create(shape, 1);
    
    if (!plane->self_model || !plane->identity_state || 
        !plane->local_image || !plane->global_image) {
        existential_plane_free(plane);
        return NULL;
    }
    
    // Initialize self-model and identity
    for (size_t i = 0; i < model_size; i++) {
        plane->self_model->data[i] = (float)rand() / RAND_MAX * 0.1f;
        plane->identity_state->data[i] = 0.0f;
        plane->local_image->data[i] = 0.0f;
        plane->global_image->data[i] = 0.0f;
    }
    
    plane->autonomy_level = 0.0f;
    plane->self_aware = false;
    plane->self_reference_degree = 0.0f;
    plane->image_convergence = 0.0f;
    plane->operational_closure = false;
    
    return plane;
}

void existential_plane_free(existential_plane_t* plane) {
    if (plane) {
        neural_tensor_free(plane->self_model);
        neural_tensor_free(plane->identity_state);
        neural_tensor_free(plane->local_image);
        neural_tensor_free(plane->global_image);
        free(plane);
    }
}

void existential_plane_update(existential_plane_t* plane, float dt) {
    if (!plane || !plane->self_model || !plane->identity_state) return;
    
    // Autognosis: Hierarchical self-image building with dual process architecture
    size_t model_size = plane->self_model->total_size;
    
    // ========================================================================
    // BOTTOM-UP INTEGRATION: Local → Global
    // Local phenomena create images of global context
    // ========================================================================
    for (size_t i = 0; i < model_size; i++) {
        // Local image integrates information about global identity
        float local_perception = 0.0f;
        for (size_t j = 0; j < model_size; j++) {
            // Local element perceives global field through weighted sampling
            float distance = fabsf((float)i - (float)j) / model_size;
            float weight = expf(-distance * distance * 2.0f);
            local_perception += plane->identity_state->data[j] * weight;
        }
        plane->local_image->data[i] = tanhf(local_perception / sqrtf(model_size));
    }
    
    // ========================================================================
    // TOP-DOWN DIFFERENTIATION: Global → Local
    // Global phenomena create images of local ensemble
    // ========================================================================
    for (size_t i = 0; i < model_size; i++) {
        // Global image differentiates based on ensemble of local states
        float global_field = 0.0f;
        for (size_t j = 0; j < model_size; j++) {
            // Global field emerges from local self-models
            float phase = 2.0f * M_PI * (float)(i - j) / model_size;
            global_field += plane->self_model->data[j] * cosf(phase);
        }
        plane->global_image->data[i] = tanhf(global_field / model_size);
    }
    
    // ========================================================================
    // RECURSIVE SELF-REFERENCE: Convergence of object and image
    // The system becomes its own reference through recursive closure
    // ========================================================================
    
    // Calculate image convergence (degree to which object equals its image)
    float convergence_sum = 0.0f;
    for (size_t i = 0; i < model_size; i++) {
        // Measure similarity between local and global images
        float diff = plane->local_image->data[i] - plane->global_image->data[i];
        convergence_sum += expf(-diff * diff);
    }
    plane->image_convergence = convergence_sum / model_size;
    
    // Self-reference degree equals consciousness level (Winiwarter)
    plane->self_reference_degree = plane->image_convergence;
    
    // Operational closure achieved when self-reference is high
    plane->operational_closure = (plane->self_reference_degree > 0.7f);
    
    // ========================================================================
    // UPDATE SELF-MODEL: Integration of local images
    // ========================================================================
    for (size_t i = 0; i < model_size; i++) {
        // Self-model updated by local images (bottom-up integration)
        float update = plane->local_image->data[i] - plane->self_model->data[i];
        plane->self_model->data[i] += update * dt * 0.2f;
    }
    
    // ========================================================================
    // UPDATE IDENTITY: Differentiation from global images
    // ========================================================================
    for (size_t i = 0; i < model_size; i++) {
        // Identity emerges from global images (top-down differentiation)
        float emergence = plane->global_image->data[i];
        
        // Include self-model coherence for recursive closure
        float coherence = 0.0f;
        for (size_t j = 0; j < model_size; j++) {
            coherence += plane->self_model->data[j] * 
                        cosf(2.0f * M_PI * (float)(i - j) / model_size);
        }
        
        // Identity integrates top-down global image and self-model coherence
        plane->identity_state->data[i] = 
            0.6f * emergence + 0.4f * tanhf(coherence / model_size);
    }
    
    // ========================================================================
    // CALCULATE AUTONOMY LEVEL
    // ========================================================================
    float identity_strength = 0.0f;
    for (size_t i = 0; i < model_size; i++) {
        identity_strength += fabsf(plane->identity_state->data[i]);
    }
    plane->autonomy_level = tanhf(identity_strength / model_size);
    
    // Autonomy enhanced by operational closure
    if (plane->operational_closure) {
        plane->autonomy_level = fminf(1.0f, plane->autonomy_level * 1.2f);
    }
    
    // Check for self-awareness threshold
    // Self-awareness emerges from both autonomy and self-reference
    plane->self_aware = (plane->autonomy_level > 0.6f && 
                        plane->self_reference_degree > 0.5f);
}

// ============================================================================
// CYCLE IMPLEMENTATIONS
// ============================================================================

cycle_state_t* cycle_create(cycle_type_t type, size_t state_size) {
    cycle_state_t* cycle = (cycle_state_t*)malloc(sizeof(cycle_state_t));
    if (!cycle) return NULL;
    
    cycle->type = type;
    cycle->activity_level = 0.5f;
    cycle->stability = 0.5f;
    cycle->is_active = true;
    
    size_t shape[1] = {state_size};
    cycle->state = neural_tensor_create(shape, 1);
    
    if (!cycle->state) {
        free(cycle);
        return NULL;
    }
    
    // Initialize state based on cycle type
    for (size_t i = 0; i < state_size; i++) {
        cycle->state->data[i] = (float)rand() / RAND_MAX * 0.5f;
    }
    
    return cycle;
}

void cycle_free(cycle_state_t* cycle) {
    if (cycle) {
        neural_tensor_free(cycle->state);
        free(cycle);
    }
}

void cycle_update(cycle_state_t* cycle, float dt) {
    if (!cycle || !cycle->state || !cycle->is_active) return;
    
    size_t state_size = cycle->state->total_size;
    
    if (cycle_is_stabilizing(cycle->type)) {
        // Stabilizing cycles dampen fluctuations
        float mean = 0.0f;
        for (size_t i = 0; i < state_size; i++) {
            mean += cycle->state->data[i];
        }
        mean /= state_size;
        
        for (size_t i = 0; i < state_size; i++) {
            float deviation = cycle->state->data[i] - mean;
            cycle->state->data[i] -= deviation * dt * 0.2f;
        }
        
        cycle->stability = 1.0f - fabsf(mean - 0.5f);
    } else {
        // Creative cycles amplify variations
        for (size_t i = 0; i < state_size; i++) {
            float noise = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
            cycle->state->data[i] += noise * dt;
            
            // Keep bounded
            if (cycle->state->data[i] > 1.0f) cycle->state->data[i] = 1.0f;
            if (cycle->state->data[i] < 0.0f) cycle->state->data[i] = 0.0f;
        }
        
        // Measure activity
        float variance = 0.0f;
        float mean = 0.5f;
        for (size_t i = 0; i < state_size; i++) {
            float diff = cycle->state->data[i] - mean;
            variance += diff * diff;
        }
        cycle->activity_level = tanhf(variance / state_size);
    }
}

bool cycle_is_stabilizing(cycle_type_t type) {
    return (type == CYCLE_VORTICES || 
            type == CYCLE_HOMEOSTASIS || 
            type == CYCLE_SELF_REFERENCE);
}

bool cycle_is_creative(cycle_type_t type) {
    return !cycle_is_stabilizing(type);
}

// ============================================================================
// SPIRAL IMPLEMENTATIONS
// ============================================================================

spiral_state_t* spiral_create(void) {
    spiral_state_t* spiral = (spiral_state_t*)malloc(sizeof(spiral_state_t));
    if (!spiral) return NULL;
    
    spiral->current_phase = PHASE_ENTROPIC_DRIFT;
    spiral->phase_completion = 0.0f;
    spiral->cycle_count = 0;
    spiral->ascending = true;
    
    return spiral;
}

void spiral_free(spiral_state_t* spiral) {
    free(spiral);
}

void spiral_advance(spiral_state_t* spiral, float progress) {
    if (!spiral) return;
    
    spiral->phase_completion += progress;
    
    // Advance to next phase when current is complete
    if (spiral->phase_completion >= 1.0f) {
        spiral->phase_completion = 0.0f;
        
        if (spiral->ascending) {
            if (spiral->current_phase < PHASE_AUTONOMY) {
                spiral->current_phase = (spiral_phase_t)((int)spiral->current_phase + 1);
            } else {
                spiral->cycle_count++;
                spiral->current_phase = PHASE_ENTROPIC_DRIFT;
            }
        }
    }
}

const char* spiral_phase_name(spiral_phase_t phase) {
    switch (phase) {
        case PHASE_ENTROPIC_DRIFT:  return "Entropic Drift";
        case PHASE_MORPHOGENESIS:   return "Morphogenesis";
        case PHASE_COMMUNICATION:   return "Communication";
        case PHASE_CYBERNETICS:     return "Cybernetics";
        case PHASE_AUTOPOIESIS:     return "Autopoiesis";
        case PHASE_SELF_REFERENCE:  return "Self-Reference";
        case PHASE_AUTONOMY:        return "Autonomy";
        default:                    return "Unknown";
    }
}

// ============================================================================
// COMPLETE SYSTEM IMPLEMENTATION
// ============================================================================

cybernetic_system_t* cybernetic_system_create(size_t n_nodes, size_t system_size) {
    cybernetic_system_t* system = (cybernetic_system_t*)malloc(sizeof(cybernetic_system_t));
    if (!system) return NULL;
    
    // Create three planes
    system->physical = physical_plane_create(n_nodes);
    system->information = information_plane_create(n_nodes);
    system->existential = existential_plane_create(system_size);
    
    if (!system->physical || !system->information || !system->existential) {
        cybernetic_system_free(system);
        return NULL;
    }
    
    // Create six cycles
    for (int i = 0; i < 6; i++) {
        system->cycles[i] = cycle_create((cycle_type_t)(i + 1), system_size);
        if (!system->cycles[i]) {
            cybernetic_system_free(system);
            return NULL;
        }
    }
    
    // Create spiral
    system->spiral = spiral_create();
    if (!system->spiral) {
        cybernetic_system_free(system);
        return NULL;
    }
    
    // Initialize system properties
    system->viability = 0.5f;
    system->complexity_level = 1.0f;
    system->is_self_organizing = false;
    system->timestep = 0;
    system->evolution_rate = 1.0f;
    
    return system;
}

void cybernetic_system_free(cybernetic_system_t* system) {
    if (system) {
        physical_plane_free(system->physical);
        information_plane_free(system->information);
        existential_plane_free(system->existential);
        
        for (int i = 0; i < 6; i++) {
            cycle_free(system->cycles[i]);
        }
        
        spiral_free(system->spiral);
        free(system);
    }
}

void cybernetic_system_step(cybernetic_system_t* system, float dt) {
    if (!system) return;
    
    dt *= system->evolution_rate;
    
    // Update all three planes
    physical_plane_update(system->physical, dt);
    information_plane_update(system->information, dt);
    existential_plane_update(system->existential, dt);
    
    // Update all six cycles
    for (int i = 0; i < 6; i++) {
        cycle_update(system->cycles[i], dt);
    }
    
    // Advance spiral based on system dynamics
    float spiral_progress = dt * (system->viability + 0.1f);
    spiral_advance(system->spiral, spiral_progress);
    
    // Calculate new viability
    system->viability = cybernetic_system_calculate_viability(system);
    
    // Check for self-organization
    system->is_self_organizing = (system->viability > 0.6f && 
                                 system->existential->autonomy_level > 0.5f);
    
    // Update complexity
    system->complexity_level = (system->physical->entropy_level +
                               system->information->complexity / 10.0f +
                               system->existential->autonomy_level) / 3.0f;
    
    system->timestep++;
}

float cybernetic_system_calculate_viability(const cybernetic_system_t* system) {
    if (!system) return 0.0f;
    
    // Viability depends on:
    // 1. Physical plane energy balance (low entropy is good)
    float physical_score = 1.0f - system->physical->entropy_level;
    
    // 2. Information plane connectivity
    float info_score = tanhf(system->information->complexity / 5.0f);
    
    // 3. Existential plane autonomy
    float existential_score = system->existential->autonomy_level;
    
    // 4. Cycle balance (need both stabilizing and creative)
    float stabilizing_activity = 0.0f;
    float creative_activity = 0.0f;
    for (int i = 0; i < 6; i++) {
        if (cycle_is_stabilizing(system->cycles[i]->type)) {
            stabilizing_activity += system->cycles[i]->activity_level;
        } else {
            creative_activity += system->cycles[i]->activity_level;
        }
    }
    float cycle_balance = tanhf(fabsf(stabilizing_activity - creative_activity));
    float cycle_score = 1.0f - cycle_balance;
    
    // Weighted average
    return (physical_score * 0.2f + 
            info_score * 0.3f + 
            existential_score * 0.3f + 
            cycle_score * 0.2f);
}

bool cybernetic_system_is_viable(const cybernetic_system_t* system) {
    return system && system->viability > 0.4f;
}

void cybernetic_system_self_organize(cybernetic_system_t* system) {
    if (!system) return;
    
    // Trigger morphogenesis and autopoiesis cycles
    if (system->cycles[1]) { // Morphogenesis
        system->cycles[1]->activity_level = 1.0f;
        system->cycles[1]->is_active = true;
    }
    
    if (system->cycles[3]) { // Autopoiesis
        system->cycles[3]->activity_level = 1.0f;
        system->cycles[3]->is_active = true;
    }
    
    system->is_self_organizing = true;
}

// ============================================================================
// LEVERAGE POINT IMPLEMENTATIONS
// ============================================================================

void cybernetic_system_intervene(cybernetic_system_t* system, 
                                leverage_point_t point,
                                float magnitude) {
    if (!system) return;
    
    // Different leverage points affect different aspects
    if (point >= LEVERAGE_CONSTANTS && point <= LEVERAGE_FLOWS) {
        // Physical plane interventions
        if (system->physical && system->physical->energy_state) {
            for (size_t i = 0; i < system->physical->n_components; i++) {
                system->physical->energy_state->data[i] += magnitude * 0.1f;
            }
        }
    } else if (point >= LEVERAGE_NEGATIVE_FEEDBACK && point <= LEVERAGE_RULES) {
        // Information plane interventions
        if (system->information && system->information->information_flow) {
            for (size_t i = 0; i < system->information->n_relations; i++) {
                system->information->information_flow->data[i] += magnitude * 0.2f;
            }
        }
    } else {
        // Existential plane interventions (most powerful)
        if (system->existential && system->existential->identity_state) {
            for (size_t i = 0; i < system->existential->identity_state->total_size; i++) {
                system->existential->identity_state->data[i] += magnitude * 0.5f;
            }
        }
        
        // High-leverage points can trigger self-organization
        if (point >= LEVERAGE_PARADIGMS) {
            system->is_self_organizing = true;
        }
    }
}

float leverage_point_effectiveness(leverage_point_t point) {
    // Higher number = more effective leverage point
    return (float)point / 12.0f;
}

const char* leverage_point_name(leverage_point_t point) {
    switch (point) {
        case LEVERAGE_CONSTANTS:         return "Constants and Parameters";
        case LEVERAGE_BUFFERS:           return "Buffers and Stocks";
        case LEVERAGE_FLOWS:             return "Material Flows";
        case LEVERAGE_NEGATIVE_FEEDBACK: return "Negative Feedback Loops";
        case LEVERAGE_POSITIVE_FEEDBACK: return "Positive Feedback Loops";
        case LEVERAGE_INFORMATION_FLOWS: return "Information Networks";
        case LEVERAGE_RULES:             return "Rules and Constraints";
        case LEVERAGE_SELF_ORGANIZATION: return "Self-Organization Capacity";
        case LEVERAGE_GOALS:             return "System Goals";
        case LEVERAGE_PARADIGMS:         return "Paradigms";
        case LEVERAGE_TRANSCENDENCE:     return "Paradigm Transcendence";
        case LEVERAGE_VALUES:            return "Core Values";
        default:                         return "Unknown";
    }
}

// ============================================================================
// ANALYSIS AND DIAGNOSTICS
// ============================================================================

void cybernetic_system_print_state(const cybernetic_system_t* system) {
    if (!system) return;
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║         THIRD-ORDER CYBERNETIC SYSTEM STATE                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Timestep: %zu\n", system->timestep);
    printf("Viability: %.3f %s\n", system->viability, 
           system->viability > 0.6f ? "(HIGH)" : 
           system->viability > 0.4f ? "(MEDIUM)" : "(LOW)");
    printf("Complexity: %.3f\n", system->complexity_level);
    printf("Self-organizing: %s\n", system->is_self_organizing ? "YES" : "NO");
    
    printf("\n--- THREE ONTOLOGICAL PLANES ---\n");
    printf("Physical Plane:\n");
    printf("  Entropy: %.3f\n", system->physical->entropy_level);
    printf("  Components: %zu\n", system->physical->n_components);
    
    printf("Information Plane:\n");
    printf("  Complexity: %.3f\n", system->information->complexity);
    printf("  Relations: %zu\n", system->information->n_relations);
    
    printf("Existential Plane:\n");
    printf("  Autonomy: %.3f\n", system->existential->autonomy_level);
    printf("  Self-aware: %s\n", system->existential->self_aware ? "YES" : "NO");
    printf("  Self-reference degree: %.3f\n", system->existential->self_reference_degree);
    printf("  Image convergence: %.3f\n", system->existential->image_convergence);
    printf("  Operational closure: %s\n", system->existential->operational_closure ? "YES" : "NO");
    
    printf("\n--- SIX CYCLES OF VIABLE SYSTEMS ---\n");
    const char* cycle_names[] = {
        "Vortices (stabilizing)",
        "Morphogenesis (creative)",
        "Homeostasis (stabilizing)",
        "Autopoiesis (creative)",
        "Self-Reference (stabilizing)",
        "Autogenesis (creative)"
    };
    
    for (int i = 0; i < 6; i++) {
        printf("%d. %s: Activity=%.3f, Stability=%.3f, %s\n",
               i + 1,
               cycle_names[i],
               system->cycles[i]->activity_level,
               system->cycles[i]->stability,
               system->cycles[i]->is_active ? "ACTIVE" : "INACTIVE");
    }
    
    printf("\n--- SPIRAL OF SELF-ORGANIZATION ---\n");
    printf("Current Phase: %s (%.0f%% complete)\n",
           spiral_phase_name(system->spiral->current_phase),
           system->spiral->phase_completion * 100.0f);
    printf("Spiral Cycles Completed: %zu\n", system->spiral->cycle_count);
    
    printf("\n═══════════════════════════════════════════════════════════════\n");
}

void cybernetic_system_analyze(const cybernetic_system_t* system) {
    if (!system) return;
    
    printf("\n=== SYSTEM ANALYSIS ===\n\n");
    
    // Analyze viability
    if (system->viability < 0.3f) {
        printf("⚠ WARNING: System viability is critically low!\n");
        printf("  Recommendations:\n");
        printf("  - Increase stabilizing cycle activity\n");
        printf("  - Reduce entropy in physical plane\n");
        printf("  - Strengthen information connectivity\n");
    } else if (system->viability > 0.8f) {
        printf("✓ System is highly viable and thriving\n");
    }
    
    // Analyze cycle balance
    float stabilizing = 0.0f, creative = 0.0f;
    for (int i = 0; i < 6; i++) {
        if (cycle_is_stabilizing(system->cycles[i]->type)) {
            stabilizing += system->cycles[i]->activity_level;
        } else {
            creative += system->cycles[i]->activity_level;
        }
    }
    
    printf("\nCycle Balance:\n");
    printf("  Stabilizing: %.3f\n", stabilizing / 3.0f);
    printf("  Creative: %.3f\n", creative / 3.0f);
    
    if (fabsf(stabilizing - creative) > 1.0f) {
        printf("  ⚠ Imbalance detected - system may be too %s\n",
               stabilizing > creative ? "rigid" : "chaotic");
    }
    
    // Analyze spiral progression
    printf("\nSpiral Evolution:\n");
    printf("  Phase: %s\n", spiral_phase_name(system->spiral->current_phase));
    
    if (system->spiral->current_phase >= PHASE_AUTOPOIESIS) {
        printf("  ✓ System has reached self-productive capability\n");
    }
    
    if (system->spiral->current_phase == PHASE_AUTONOMY) {
        printf("  ✓ System has achieved full autonomy!\n");
    }
    
    // Recommend leverage points
    printf("\nRecommended Leverage Points:\n");
    if (system->viability < 0.5f) {
        printf("  1. %s (effectiveness: %.2f)\n", 
               leverage_point_name(LEVERAGE_SELF_ORGANIZATION),
               leverage_point_effectiveness(LEVERAGE_SELF_ORGANIZATION));
        printf("  2. %s (effectiveness: %.2f)\n",
               leverage_point_name(LEVERAGE_INFORMATION_FLOWS),
               leverage_point_effectiveness(LEVERAGE_INFORMATION_FLOWS));
    } else {
        printf("  1. %s (effectiveness: %.2f)\n",
               leverage_point_name(LEVERAGE_PARADIGMS),
               leverage_point_effectiveness(LEVERAGE_PARADIGMS));
        printf("  2. %s (effectiveness: %.2f)\n",
               leverage_point_name(LEVERAGE_GOALS),
               leverage_point_effectiveness(LEVERAGE_GOALS));
    }
}

char* cybernetic_system_export_state(const cybernetic_system_t* system) {
    if (!system) return NULL;
    
    // Allocate buffer for export
    char* buffer = (char*)malloc(4096);
    if (!buffer) return NULL;
    
    snprintf(buffer, 4096,
             "(cybernetic-system\n"
             "  (timestep %zu)\n"
             "  (viability %.3f)\n"
             "  (complexity %.3f)\n"
             "  (self-organizing %s)\n"
             "  (physical (entropy %.3f))\n"
             "  (information (complexity %.3f))\n"
             "  (existential (autonomy %.3f))\n"
             "  (spiral-phase %s)\n"
             "  (spiral-completion %.3f)\n"
             ")",
             system->timestep,
             system->viability,
             system->complexity_level,
             system->is_self_organizing ? "#t" : "#f",
             system->physical->entropy_level,
             system->information->complexity,
             system->existential->autonomy_level,
             spiral_phase_name(system->spiral->current_phase),
             system->spiral->phase_completion);
    
    return buffer;
}
