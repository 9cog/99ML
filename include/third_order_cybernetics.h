/**
 * third_order_cybernetics.h
 * 
 * Third-Order Cybernetics Model
 * Implementation of Eric Schwarz's holistic metamodel for understanding
 * self-organizing systems across physical, biological, social, and cognitive domains.
 * 
 * Core Concepts:
 * - Three ontological planes: Physical (energy), Information (relations), Existential (being)
 * - Six cycles of viable systems (3 stabilizing, 3 creative)
 * - Spiral of self-organization (7 phases: entropic drift through autonomy)
 * - Twelve leverage points for system intervention
 */

#ifndef THIRD_ORDER_CYBERNETICS_H
#define THIRD_ORDER_CYBERNETICS_H

#include <stddef.h>
#include <stdbool.h>
#include "neural_physics.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// THREE ONTOLOGICAL PLANES
// ============================================================================

/**
 * Physical Plane - Energy, objects, material components
 * The substrate of matter and energy transformations
 */
typedef struct {
    neural_tensor_t* energy_state;      // Energy distribution
    neural_tensor_t* matter_structure;  // Material organization
    float entropy_level;                // System entropy
    size_t n_components;                // Number of physical components
} physical_plane_t;

/**
 * Information Plane - Relations, networks of potential and actual connections
 * The realm of patterns, connections, and information flow
 */
typedef struct {
    neural_tensor_t* connectivity;      // Network of relations
    neural_tensor_t* information_flow;  // Information dynamics
    float complexity;                   // Network complexity measure
    size_t n_relations;                 // Number of relations
} information_plane_t;

/**
 * Existential Plane - Being, emerging wholeness
 * The plane of autonomy, self-reference, and emergent identity
 * Enhanced with autognostic (hierarchical self-image building) processes
 */
typedef struct {
    neural_tensor_t* self_model;        // System's model of itself
    neural_tensor_t* identity_state;    // Emergent identity
    float autonomy_level;               // Degree of autonomy
    bool self_aware;                    // Self-awareness flag
    
    // Autognosis: Hierarchical self-image building
    neural_tensor_t* local_image;       // Local image of global context (bottom-up)
    neural_tensor_t* global_image;      // Global image of local ensemble (top-down)
    float self_reference_degree;        // Degree of self-reference (consciousness level)
    float image_convergence;            // Convergence between object and image
    bool operational_closure;           // System is its own reference
} existential_plane_t;

// ============================================================================
// SIX CYCLES OF VIABLE SYSTEMS
// ============================================================================

/**
 * Cycle types: 3 stabilizing (enabling persistence) + 3 creative (enabling change)
 */
typedef enum {
    CYCLE_VORTICES = 1,        // Physical recycling of matter and energy (stabilizing)
    CYCLE_MORPHOGENESIS = 2,   // Self-organization creating new structures (creative)
    CYCLE_HOMEOSTASIS = 3,     // Functional feedback maintaining regulation (stabilizing)
    CYCLE_AUTOPOIESIS = 4,     // Self-production of living systems (creative)
    CYCLE_SELF_REFERENCE = 5,  // Existential autonomy and self-knowledge (stabilizing)
    CYCLE_AUTOGENESIS = 6      // Self-creation leading to autonomy (creative)
} cycle_type_t;

/**
 * State of a system cycle
 */
typedef struct {
    cycle_type_t type;
    float activity_level;       // Current activity (0.0 to 1.0)
    float stability;            // Stability measure
    bool is_active;             // Whether cycle is currently operating
    neural_tensor_t* state;     // Internal state representation
} cycle_state_t;

// ============================================================================
// SPIRAL OF SELF-ORGANIZATION
// ============================================================================

/**
 * Seven phases of the self-organization spiral
 */
typedef enum {
    PHASE_ENTROPIC_DRIFT = 0,    // Non-linear conditions far from equilibrium
    PHASE_MORPHOGENESIS = 1,     // Differentiation via positive feedback
    PHASE_COMMUNICATION = 2,     // Fluxes establishing networks
    PHASE_CYBERNETICS = 3,       // Causal networks influencing development
    PHASE_AUTOPOIESIS = 4,       // Self-productive cycle emergence
    PHASE_SELF_REFERENCE = 5,    // Recursivity where machine and image converge
    PHASE_AUTONOMY = 6           // System actualization according to own rules
} spiral_phase_t;

/**
 * Spiral state tracker
 */
typedef struct {
    spiral_phase_t current_phase;
    float phase_completion;      // Progress in current phase (0.0 to 1.0)
    size_t cycle_count;          // Number of complete spirals
    bool ascending;              // Direction of movement
} spiral_state_t;

// ============================================================================
// TWELVE LEVERAGE POINTS
// ============================================================================

/**
 * System intervention leverage points (ordered by increasing effectiveness)
 * Based on Donella Meadows framework, adapted for third-order cybernetics
 */
typedef enum {
    // Physical plane (lowest leverage)
    LEVERAGE_CONSTANTS = 1,           // Numbers, parameters, constants
    LEVERAGE_BUFFERS = 2,             // Stabilizing stocks and buffers
    LEVERAGE_FLOWS = 3,               // Structure of material flows
    
    // Information plane (medium leverage)
    LEVERAGE_NEGATIVE_FEEDBACK = 4,   // Negative feedback loop strength
    LEVERAGE_POSITIVE_FEEDBACK = 5,   // Positive feedback regulation
    LEVERAGE_INFORMATION_FLOWS = 6,   // Information flow networks
    LEVERAGE_RULES = 7,               // Social rules and constraints
    
    // Existential plane (highest leverage)
    LEVERAGE_SELF_ORGANIZATION = 8,   // Capacity for self-organization
    LEVERAGE_GOALS = 9,               // System goals and purposes
    LEVERAGE_PARADIGMS = 10,          // Paradigms and worldviews
    LEVERAGE_TRANSCENDENCE = 11,      // Ability to transcend paradigms
    LEVERAGE_VALUES = 12              // Core values and purpose
} leverage_point_t;

// ============================================================================
// COMPLETE THIRD-ORDER CYBERNETIC SYSTEM
// ============================================================================

/**
 * Complete third-order cybernetic system integrating all components
 */
typedef struct {
    // Three planes
    physical_plane_t* physical;
    information_plane_t* information;
    existential_plane_t* existential;
    
    // Six cycles
    cycle_state_t* cycles[6];
    
    // Spiral evolution
    spiral_state_t* spiral;
    
    // System properties
    float viability;                 // Overall system viability (0.0 to 1.0)
    float complexity_level;          // System complexity measure
    bool is_self_organizing;         // Currently self-organizing
    
    // Time evolution
    size_t timestep;
    float evolution_rate;
} cybernetic_system_t;

// ============================================================================
// CREATION AND DESTRUCTION
// ============================================================================

/**
 * Create a new third-order cybernetic system
 */
cybernetic_system_t* cybernetic_system_create(size_t n_nodes, size_t system_size);

/**
 * Free cybernetic system resources
 */
void cybernetic_system_free(cybernetic_system_t* system);

// ============================================================================
// PLANE OPERATIONS
// ============================================================================

/**
 * Create individual planes
 */
physical_plane_t* physical_plane_create(size_t n_components);
information_plane_t* information_plane_create(size_t n_relations);
existential_plane_t* existential_plane_create(size_t model_size);

/**
 * Free individual planes
 */
void physical_plane_free(physical_plane_t* plane);
void information_plane_free(information_plane_t* plane);
void existential_plane_free(existential_plane_t* plane);

/**
 * Update plane states
 */
void physical_plane_update(physical_plane_t* plane, float dt);
void information_plane_update(information_plane_t* plane, float dt);
void existential_plane_update(existential_plane_t* plane, float dt);

// ============================================================================
// CYCLE OPERATIONS
// ============================================================================

/**
 * Create a cycle state
 */
cycle_state_t* cycle_create(cycle_type_t type, size_t state_size);

/**
 * Free cycle state
 */
void cycle_free(cycle_state_t* cycle);

/**
 * Update cycle (execute one iteration)
 */
void cycle_update(cycle_state_t* cycle, float dt);

/**
 * Check if cycle is stabilizing or creative
 */
bool cycle_is_stabilizing(cycle_type_t type);
bool cycle_is_creative(cycle_type_t type);

// ============================================================================
// SPIRAL OPERATIONS
// ============================================================================

/**
 * Create spiral state
 */
spiral_state_t* spiral_create(void);

/**
 * Free spiral state
 */
void spiral_free(spiral_state_t* spiral);

/**
 * Advance spiral to next phase
 */
void spiral_advance(spiral_state_t* spiral, float progress);

/**
 * Get phase name as string
 */
const char* spiral_phase_name(spiral_phase_t phase);

// ============================================================================
// SYSTEM EVOLUTION
// ============================================================================

/**
 * Evolve the complete system by one timestep
 * Integrates all planes, cycles, and spiral dynamics
 */
void cybernetic_system_step(cybernetic_system_t* system, float dt);

/**
 * Calculate system viability based on all components
 */
float cybernetic_system_calculate_viability(const cybernetic_system_t* system);

/**
 * Check if system is in a viable state
 */
bool cybernetic_system_is_viable(const cybernetic_system_t* system);

/**
 * Trigger self-organization process
 */
void cybernetic_system_self_organize(cybernetic_system_t* system);

// ============================================================================
// LEVERAGE POINT INTERVENTIONS
// ============================================================================

/**
 * Apply intervention at a specific leverage point
 */
void cybernetic_system_intervene(cybernetic_system_t* system, 
                                leverage_point_t point,
                                float magnitude);

/**
 * Get leverage point effectiveness (higher is more effective)
 */
float leverage_point_effectiveness(leverage_point_t point);

/**
 * Get leverage point name
 */
const char* leverage_point_name(leverage_point_t point);

// ============================================================================
// ANALYSIS AND DIAGNOSTICS
// ============================================================================

/**
 * Get current system state summary
 */
void cybernetic_system_print_state(const cybernetic_system_t* system);

/**
 * Analyze system dynamics
 */
void cybernetic_system_analyze(const cybernetic_system_t* system);

/**
 * Export system state for visualization
 */
char* cybernetic_system_export_state(const cybernetic_system_t* system);

#ifdef __cplusplus
}
#endif

#endif // THIRD_ORDER_CYBERNETICS_H
