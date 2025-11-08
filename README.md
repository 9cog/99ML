# 99ML - Genesis of Inference: Neural-Symbolic Symbiosis

A neural-symbolic cognitive architecture that unifies symbolic reasoning with neural computation.

## Overview

99ML implements a dual-layer cognitive system:

- **Mind Layer (Scheme)**: Defines cognitive grammar, patterns, and rules of inference
- **Brain Layer (C/ggml)**: Implements the underlying "physics" - tensor operations, activation landscapes, and attention mechanisms

This symbiosis enables systems that can both reason symbolically and process information through continuous neural dynamics.

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    COGNITIVE LAYER (Mind)                    │
│                        Scheme                                │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ • Cognitive Grammar                                 │    │
│  │ • Inference Rules (modus ponens, unification, etc.) │    │
│  │ • Pattern Matching                                  │    │
│  │ • Symbolic Reasoning (deduction, induction, analogy)│    │
│  │ • Working Memory                                    │    │
│  └─────────────────────────────────────────────────────┘    │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        │ Neural-Symbolic Bridge
                        │
┌───────────────────────▼─────────────────────────────────────┐
│                  NEURAL PHYSICS LAYER (Brain)                │
│                         C/ggml                               │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ • Tensor Operations (matmul, add, activations)      │    │
│  │ • Activation Landscape                              │    │
│  │ • Attention Mechanisms (self-attention, multi-head) │    │
│  │ • Spreading Activation                              │    │
│  │ • Cognitive Context                                 │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

## Components

### Scheme Layer (Mind)

**Location**: `scheme/cognitive-grammar.scm`

Core cognitive operations:
- `(concept name properties)` - Create concepts
- `(relation type from to)` - Define relations
- `(pattern name structure)` - Define patterns

Inference rules:
- `(modus-ponens antecedent consequent premise)` - Basic inference
- `(unify pattern1 pattern2)` - Pattern unification
- `(chain-inference rule1 rule2)` - Chain rules

Cognitive operations:
- `(abstract-from concrete-pattern)` - Abstraction
- `(analogy source target mapping)` - Analogy making
- `(deduce premises rules)` - Deductive reasoning
- `(induce examples)` - Inductive reasoning

Neural-symbolic interface:
- `(encode-symbolic-to-neural form)` - Encode for neural processing
- `(decode-neural-to-symbolic output)` - Decode neural output
- `(neural-compute operation tensors)` - Execute neural operations

### C/ggml Layer (Brain)

**Headers**: `include/neural_physics.h`  
**Implementation**: `src/neural_physics.c`

Tensor operations:
- `neural_tensor_create()` - Create tensors
- `neural_matmul()` - Matrix multiplication
- `neural_add()`, `neural_mul()` - Element-wise operations
- `neural_relu()`, `neural_softmax()`, `neural_tanh()` - Activations

Activation landscape:
- `activation_landscape_create()` - Create activation state
- `activation_landscape_spread()` - Spread activation
- `activation_landscape_get_active_nodes()` - Query active nodes

Attention mechanisms:
- `attention_compute()` - Scaled dot-product attention
- `attention_multihead()` - Multi-head attention
- `attention_self()` - Self-attention

Cognitive context:
- `cognitive_context_create()` - Complete cognitive state
- `cognitive_context_step()` - Update state
- `cognitive_context_get_state()` - Query state

### Bridge Layer

**Implementation**: `src/scheme_neural_bridge.c`

Enables bidirectional communication:
- `scheme_list_to_tensor()` - Convert Scheme data to tensors
- `tensor_to_scheme_list()` - Convert tensors to Scheme
- `scheme_neural_compute()` - Execute neural ops from Scheme
- `scheme_spread_activation()` - Control activation spreading
- `scheme_apply_attention()` - Apply attention from Scheme

## Building

### Requirements
- CMake 3.10 or higher
- C compiler (GCC, Clang, or compatible)
- Scheme interpreter (Guile, Chez Scheme, or similar) for running Scheme examples

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
make

# Run demo
./neural_symbolic_demo
```

## Running Examples

### C Demo
```bash
./build/neural_symbolic_demo
```

Demonstrates:
- Tensor operations (matrix multiplication)
- Activation functions (ReLU, tanh, softmax)
- Self-attention mechanism
- Cognitive context with activation landscape

### Scheme Demo
```bash
scheme examples/neural-symbolic-demo.scm
# or
guile examples/neural-symbolic-demo.scm
```

Demonstrates:
- Concept creation and relations
- Inference rules and unification
- Activation patterns and attention
- Working memory
- Complex reasoning (abstraction, analogy, deduction, induction)

## Key Concepts

### Neural-Symbolic Symbiosis

The architecture bridges two paradigms:

1. **Symbolic (Mind)**: Discrete, compositional, rule-based reasoning
2. **Neural (Brain)**: Continuous, distributed, learned representations

This enables:
- **Grounded reasoning**: Symbolic operations backed by neural activations
- **Interpretable learning**: Neural patterns decoded to symbolic rules
- **Hybrid inference**: Combining logical and statistical reasoning
- **Emergent cognition**: Complex behavior from mind-brain interaction

### Activation Landscape

Represents the neural substrate as a continuous space where:
- Concepts are nodes with activation values
- Relations are connectivity patterns
- Reasoning is spreading activation
- Attention modulates information flow

### Cognitive Context

Maintains the complete cognitive state:
- Current activation landscape
- Attention state
- Working memory
- Computational history

## Future Directions

- Integration with actual ggml library for optimized tensor operations
- Extended Scheme interpreter with FFI bindings
- Learning mechanisms (gradient descent, symbolic rule learning)
- Memory consolidation and knowledge graphs
- Multi-modal representations
- Embodied cognition interfaces

## License

GNU Affero General Public License v3.0 (AGPL-3.0)

## Philosophy

> "The mind is not a vessel to be filled, but a fire to be kindled."  
> — Plutarch

This project explores the hypothesis that intelligence emerges from the interplay between:
- The **symbolic realm** of concepts, rules, and logic
- The **subsymbolic realm** of continuous activations and learned patterns

By implementing both layers and their bridge, we create a computational substrate for exploring cognitive architectures that transcend either paradigm alone.
