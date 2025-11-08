# Neural-Symbolic Symbiosis Architecture

## System Overview

```
┌─────────────────────────────────────────────────────────────────────┐
│                         USER INTERFACE                               │
│  • Scheme REPL for symbolic interaction                             │
│  • C API for neural computation                                     │
└────────────────────┬────────────────────────────────────────────────┘
                     │
     ┌───────────────▼──────────────────┐
     │    NEURAL-SYMBOLIC BRIDGE        │
     │  scheme_neural_bridge.c          │
     │  • scheme_list_to_tensor()       │
     │  • tensor_to_scheme_list()       │
     │  • scheme_neural_compute()       │
     │  • scheme_spread_activation()    │
     └───┬──────────────────────────┬───┘
         │                          │
         │                          │
┌────────▼─────────┐       ┌────────▼──────────┐
│   MIND LAYER     │       │   BRAIN LAYER     │
│   (Scheme)       │       │   (C/ggml)        │
│                  │       │                   │
│ cognitive-       │       │ neural_physics.c  │
│ grammar.scm      │       │                   │
│                  │       │                   │
│ • Concepts       │       │ • Tensors         │
│ • Relations      │       │ • Matrix ops      │
│ • Patterns       │       │ • Activations     │
│ • Inference      │       │ • Attention       │
│ • Unification    │       │ • Landscapes      │
│ • Reasoning      │       │ • Contexts        │
│                  │       │                   │
└──────────────────┘       └───────────────────┘
```

## Component Details

### Mind Layer (Scheme)

**File**: `scheme/cognitive-grammar.scm`

Provides high-level symbolic reasoning:

1. **Cognitive Primitives**
   - Concept representation
   - Relation definition
   - Pattern specification

2. **Inference Engine**
   - Modus ponens
   - Rule chaining
   - Pattern unification

3. **Reasoning Mechanisms**
   - Abstraction
   - Analogy
   - Deduction
   - Induction

4. **Working Memory**
   - Item storage
   - Query interface
   - Memory management

### Brain Layer (C)

**Files**: 
- `include/neural_physics.h`
- `src/neural_physics.c`

Provides low-level neural computation:

1. **Tensor Operations**
   ```c
   neural_tensor_t* neural_matmul(A, B)
   neural_tensor_t* neural_add(A, B)
   neural_tensor_t* neural_mul(A, B)
   ```

2. **Activation Functions**
   ```c
   neural_tensor_t* neural_relu(input)
   neural_tensor_t* neural_softmax(input)
   neural_tensor_t* neural_tanh(input)
   ```

3. **Activation Landscape**
   ```c
   activation_landscape_t* landscape
   activation_landscape_spread(landscape, connectivity, decay)
   activation_landscape_get_active_nodes(landscape)
   ```

4. **Attention Mechanisms**
   ```c
   attention_compute(state, query, key, value)
   attention_multihead(state, input)
   attention_self(input, n_heads)
   ```

5. **Cognitive Context**
   ```c
   cognitive_context_t* context
   cognitive_context_step(context, input)
   cognitive_context_get_state(context)
   ```

### Bridge Layer

**File**: `src/scheme_neural_bridge.c`

Enables communication between layers:

1. **Data Conversion**
   - Symbolic → Neural: `scheme_list_to_tensor()`
   - Neural → Symbolic: `tensor_to_scheme_list()`

2. **Operation Bridge**
   - Execute neural ops from Scheme
   - Control activation spreading
   - Apply attention mechanisms
   - Query cognitive state

## Data Flow

### Example: Symbolic Query with Neural Grounding

```
1. User: (concept 'cat '((mammal #t)))
   ↓
2. Scheme creates symbolic representation
   ↓
3. Bridge: scheme_list_to_tensor()
   ↓
4. C: Creates activation in neural landscape
   ↓
5. C: Spreads activation through connectivity
   ↓
6. Bridge: tensor_to_scheme_list()
   ↓
7. Scheme: Returns activated concepts
   ↓
8. User: Receives inference results
```

### Example: Neural Computation from Scheme

```
1. User: (neural-compute 'matmul tensor1 tensor2)
   ↓
2. Scheme: Calls bridge interface
   ↓
3. Bridge: Converts Scheme tensors to C
   ↓
4. C: Executes neural_matmul()
   ↓
5. Bridge: Converts result back to Scheme
   ↓
6. User: Receives computed tensor
```

## Design Principles

### 1. Dual Representation
- Symbolic: Discrete, compositional, interpretable
- Neural: Continuous, distributed, learnable

### 2. Bidirectional Flow
- Top-down: Symbolic control of neural processes
- Bottom-up: Neural patterns inform symbolic reasoning

### 3. Grounded Symbols
- Every symbolic concept has neural grounding
- Every neural pattern can be symbolically interpreted

### 4. Unified Memory
- Working memory spans both layers
- Cognitive context maintains coherent state

### 5. Emergent Cognition
- Intelligence emerges from interaction
- Neither layer alone is sufficient

## Performance Characteristics

### Symbolic Layer (Scheme)
- **Strengths**: Exact reasoning, compositionality, interpretability
- **Weaknesses**: Brittleness, manual rule creation, combinatorial explosion

### Neural Layer (C/ggml)
- **Strengths**: Robustness, learning, pattern recognition
- **Weaknesses**: Black box, requires data, local minima

### Combined System
- **Strengths**: Best of both worlds
- **Approach**: Use symbols for structure, neural for uncertainty

## Extension Points

### 1. Learning Integration
- Add gradient-based optimization
- Implement neural-symbolic learning
- Enable rule extraction from neural patterns

### 2. Knowledge Graphs
- Extend to graph neural networks
- Add semantic memory
- Implement conceptual blending

### 3. Multi-Modal Processing
- Vision: CNN activations + symbolic descriptions
- Language: Transformers + grammar rules
- Audio: Spectrograms + phonetic patterns

### 4. Embodiment
- Sensorimotor grounding
- Action-perception loops
- Environmental interaction

## Future Directions

1. **ggml Integration**: Replace custom tensor ops with actual ggml library
2. **Scheme FFI**: Add C foreign function interface to Scheme
3. **Learning**: Implement backpropagation and symbolic rule learning
4. **Scaling**: Optimize for large knowledge bases and neural models
5. **Applications**: Natural language, robotics, scientific reasoning
