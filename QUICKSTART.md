# Quick Start Guide

## Installation

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y build-essential cmake

# macOS
brew install cmake

# Fedora/RHEL
sudo dnf install gcc cmake make
```

### Build

```bash
# Clone the repository
git clone https://github.com/9cog/99ML.git
cd 99ML

# Build
mkdir build
cd build
cmake ..
make

# Run demo
./neural_symbolic_demo
```

## Quick Examples

### Example 1: Basic Tensor Operations

```c
#include "neural_physics.h"

// Create tensors
size_t shape[2] = {3, 3};
neural_tensor_t* A = neural_tensor_create(shape, 2);
neural_tensor_t* B = neural_tensor_create(shape, 2);

// Initialize with data
for (size_t i = 0; i < 9; i++) {
    A->data[i] = i;
    B->data[i] = i * 2;
}

// Compute
neural_tensor_t* C = neural_add(A, B);
neural_tensor_t* D = neural_matmul(A, B);

// Cleanup
neural_tensor_free(A);
neural_tensor_free(B);
neural_tensor_free(C);
neural_tensor_free(D);
```

### Example 2: Activation Landscape

```c
// Create cognitive context
cognitive_context_t* ctx = cognitive_context_create(10, 100);

// Set activations
float activations[10] = {0.8, 0.6, 0.3, 0.9, 0.2, 
                         0.7, 0.4, 0.1, 0.5, 0.85};
activation_landscape_update(ctx->landscape, activations);

// Query active nodes
size_t n_active = 0;
size_t* active = activation_landscape_get_active_nodes(
    ctx->landscape, &n_active);

// Use results...

free(active);
cognitive_context_free(ctx);
```

### Example 3: Attention Mechanism

```c
// Create input sequence
size_t shape[2] = {4, 8};  // 4 tokens, 8 dimensions
neural_tensor_t* input = neural_tensor_create(shape, 2);

// Initialize data
for (size_t i = 0; i < input->total_size; i++) {
    input->data[i] = (float)i / input->total_size;
}

// Apply self-attention
neural_tensor_t* output = attention_self(input, 2);

neural_tensor_free(input);
neural_tensor_free(output);
```

### Example 4: Scheme Cognitive Reasoning

```scheme
#!/usr/bin/env scheme

(load "scheme/cognitive-grammar.scm")

;; Create concepts
(define cat (concept 'cat '((mammal #t) (meows #t))))
(define mammal (concept 'mammal '((animate #t))))

;; Define relation
(define cat-is-mammal (relation 'is-a cat mammal))

;; Inference
(define conclusion (modus-ponens 
    '(cat-is-mammal) 
    '(mammals-breathe) 
    '(cat-is-mammal)))

;; Pattern matching
(define pattern1 '(likes ?x cats))
(define pattern2 '(likes john ?y))
(define unified (unify pattern1 pattern2))

;; Display results
(display unified)
```

### Example 5: Neural-Symbolic Bridge

```c
// Initialize bridge
bridge_init();

// Create context
cognitive_context_t* ctx = cognitive_context_create(10, 100);

// Set activations from Scheme
float act[10] = {0.9, 0.1, 0.8, 0.2, 0.7, 0.3, 0.6, 0.4, 0.5, 0.5};
activation_landscape_update(ctx->landscape, act);

// Spread activation
scheme_spread_activation(ctx, 0.8);

// Get active concepts
char* active = scheme_get_active_concepts(ctx);
printf("Active concepts: %s\n", active);

free(active);
cognitive_context_free(ctx);
bridge_shutdown();
```

## Common Patterns

### Pattern 1: Create-Process-Cleanup

```c
// 1. Create resources
neural_tensor_t* tensor = neural_tensor_create(shape, n_dims);

// 2. Process
neural_tensor_t* result = neural_relu(tensor);

// 3. Cleanup
neural_tensor_free(tensor);
neural_tensor_free(result);
```

### Pattern 2: Context Management

```c
// 1. Create context
cognitive_context_t* ctx = cognitive_context_create(n_nodes, capacity);

// 2. Use context
cognitive_context_step(ctx, input);
neural_tensor_t* state = cognitive_context_get_state(ctx);

// 3. Cleanup
neural_tensor_free(state);
cognitive_context_free(ctx);
```

### Pattern 3: Symbolic-Neural Round Trip

```c
// 1. Symbolic to neural
neural_tensor_t* tensor = encode_symbolic("(concept cat)");

// 2. Neural processing
neural_tensor_t* result = neural_softmax(tensor);

// 3. Neural to symbolic
char* symbolic = decode_neural(result);

// 4. Cleanup
neural_tensor_free(tensor);
neural_tensor_free(result);
free(symbolic);
```

## Troubleshooting

### Build Issues

**Problem**: CMake not found
```bash
# Install CMake
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake          # macOS
```

**Problem**: Compiler errors
```bash
# Ensure you have a C compiler
gcc --version
# or
clang --version
```

### Runtime Issues

**Problem**: Segmentation fault
- Check that all pointers are initialized
- Verify tensor shapes match for operations
- Ensure proper cleanup order

**Problem**: Memory leaks
- Always free tensors after use
- Free contexts before program exit
- Check Valgrind output: `valgrind ./neural_symbolic_demo`

## Next Steps

1. **Read** the [Architecture documentation](ARCHITECTURE.md)
2. **Explore** the [examples](examples/) directory
3. **Modify** the Scheme grammar in `scheme/cognitive-grammar.scm`
4. **Extend** the neural operations in `src/neural_physics.c`
5. **Integrate** with your application

## Getting Help

- Check the [README](README.md) for detailed information
- Review the [Architecture](ARCHITECTURE.md) document
- Examine the example code
- Read the header files for API documentation

## Contributing

Contributions welcome! Areas of interest:

1. Integration with actual ggml library
2. Advanced attention mechanisms
3. Learning algorithms
4. More Scheme inference rules
5. Performance optimizations
6. Documentation improvements

## License

GNU Affero General Public License v3.0 (AGPL-3.0)
