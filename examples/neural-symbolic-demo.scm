#!/usr/bin/env scheme
;;; neural-symbolic-demo.scm
;;; Demonstration of the cognitive layer integration with neural physics

(load "scheme/cognitive-grammar.scm")

;; ============================================================================
;; DEMO: Cognitive Reasoning with Neural Grounding
;; ============================================================================

(display "╔═══════════════════════════════════════════════════════════════╗\n")
(display "║   Neural-Symbolic Symbiosis - Scheme Cognitive Layer         ║\n")
(display "╚═══════════════════════════════════════════════════════════════╝\n\n")

;; Demo 1: Concept creation and relationships
(display "=== Demo 1: Concept Creation ===\n")
(define mammal (concept 'mammal '((animate #t) (warm-blooded #t))))
(define cat (concept 'cat '((mammal #t) (has-tail #t) (meows #t))))
(define dog (concept 'dog '((mammal #t) (has-tail #t) (barks #t))))

(display "Created concepts:\n")
(display "  Mammal: ") (display mammal) (newline)
(display "  Cat: ") (display cat) (newline)
(display "  Dog: ") (display dog) (newline)
(newline)

;; Demo 2: Relations
(display "=== Demo 2: Relations ===\n")
(define cat-is-mammal (relation 'is-a cat mammal))
(define dog-is-mammal (relation 'is-a dog mammal))

(display "Created relations:\n")
(display "  ") (display cat-is-mammal) (newline)
(display "  ") (display dog-is-mammal) (newline)
(newline)

;; Demo 3: Inference rules
(display "=== Demo 3: Inference Rules ===\n")

;; Define an inference rule
(define rule1 '(cat-is-mammal))
(define rule2 '(mammal-is-animal))

;; Apply modus ponens
(display "Applying modus ponens:\n")
(display "  If cat-is-mammal AND we have cat-is-mammal, then derive truth\n")
(define result1 (modus-ponens '(cat-is-mammal) '(#t) '(cat-is-mammal)))
(display "  Result: ") (display result1) (newline)
(newline)

;; Demo 4: Unification
(display "=== Demo 4: Pattern Unification ===\n")
(define pattern1 '(loves ?x cat))
(define pattern2 '(loves john ?y))

(display "Pattern 1: ") (display pattern1) (newline)
(display "Pattern 2: ") (display pattern2) (newline)
(display "Unification: ") (display (unify pattern1 pattern2)) (newline)
(newline)

;; Demo 5: Activation patterns
(display "=== Demo 5: Activation Patterns ===\n")
(define act1 (activation-pattern 'cat 0.8))
(define act2 (activation-pattern 'dog 0.6))
(define act3 (activation-pattern 'mammal 0.9))

(display "Activation patterns:\n")
(display "  ") (display act1) (newline)
(display "  ") (display act2) (newline)
(display "  ") (display act3) (newline)
(newline)

;; Demo 6: Attention mechanism
(display "=== Demo 6: Attention Mechanism ===\n")
(define concepts '(cat dog mammal))
(define weights '(0.5 0.3 0.2))
(define attention (attention-focus concepts weights))

(display "Attention focus:\n")
(display "  ") (display attention) (newline)
(newline)

;; Demo 7: Working memory
(display "=== Demo 7: Working Memory ===\n")
(clear-working-memory)
(add-to-working-memory cat)
(add-to-working-memory dog)
(add-to-working-memory act1)

(display "Working memory contents:\n")
(display "  ") (display working-memory) (newline)
(newline)

;; Demo 8: Neural-symbolic interface
(display "=== Demo 8: Neural-Symbolic Interface ===\n")
(define symbolic-form '(concept cat))
(define encoded (encode-symbolic-to-neural symbolic-form))

(display "Symbolic form: ") (display symbolic-form) (newline)
(display "Encoded for neural processing: ") (display encoded) (newline)

;; Simulate neural computation
(define neural-op (neural-compute 'matmul '(tensor1 tensor2)))
(display "Neural computation request: ") (display neural-op) (newline)
(newline)

;; Demo 9: Complex reasoning
(display "=== Demo 9: Complex Reasoning ===\n")

;; Abstraction
(define concrete '((cat meows) (dog barks)))
(define abstract-rule (abstract-from concrete))
(display "Abstraction from concrete examples:\n")
(display "  Concrete: ") (display concrete) (newline)
(display "  Abstract: ") (display abstract-rule) (newline)
(newline)

;; Analogy
(define source-domain '(solar-system (sun planets)))
(define target-domain '(atom (nucleus electrons)))
(define analogy-map (analogy source-domain target-domain '((sun . nucleus) (planets . electrons))))
(display "Analogy mapping:\n")
(display "  ") (display analogy-map) (newline)
(newline)

;; Deduction
(define premises '((all-mammals-breathe) (cat-is-mammal)))
(define deduction-rules '((A -> B) (A) (therefore B)))
(define deduced (deduce premises deduction-rules))
(display "Deductive reasoning:\n")
(display "  Premises: ") (display premises) (newline)
(display "  Conclusion: ") (display deduced) (newline)
(newline)

;; Induction
(define examples '((cat-meows) (felix-meows) (whiskers-meows)))
(define induced (induce examples))
(display "Inductive reasoning:\n")
(display "  Examples: ") (display examples) (newline)
(display "  Induced rule: ") (display induced) (newline)
(newline)

;; Demo 10: Spreading activation
(display "=== Demo 10: Spreading Activation ===\n")
(define spread (spread-activation act1 0.5))
(display "Spreading activation from: ") (display act1) (newline)
(display "Spread pattern: ") (display spread) (newline)
(newline)

(display "╔═══════════════════════════════════════════════════════════════╗\n")
(display "║                    Cognitive Layer Demo Complete              ║\n")
(display "║                                                               ║\n")
(display "║  The Scheme layer provides:                                  ║\n")
(display "║  • Symbolic reasoning and inference                          ║\n")
(display "║  • Pattern matching and unification                          ║\n")
(display "║  • Cognitive grammar and rules                               ║\n")
(display "║  • Interface to neural substrate                             ║\n")
(display "╚═══════════════════════════════════════════════════════════════╝\n")
