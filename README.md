# Cryptography & Security Algorithms — KaTeX Cheatsheet

> [!NOTE]
> **AI Disclosure:** This `README.md` and documentation cheatsheet was **AI-generated**.  
> However, all source code implementations (`*.cpp`) in this repository are **handwritten and human-crafted**.

---

## Table of Contents
1. [Repository Overview](#repository-overview)
2. [Mathematical Foundations & Number Theory](#mathematical-foundations--number-theory)
   - [Extended Euclidean Algorithm & Bézout's Identity](#extended-euclidean-algorithm--bezouts-identity)
   - [Modular Multiplicative Inverse](#modular-multiplicative-inverse)
   - [Modular Exponentiation (Binary Exponentiation)](#modular-exponentiation-binary-exponentiation)
   - [Euler's Totient Function](#eulers-totient-function)
   - [Primitive Roots & Generator Testing](#primitive-roots--generator-testing)
3. [Classical Ciphers](#classical-ciphers)
   - [Caesar Cipher](#caesar-cipher)
   - [Vernam Cipher (One-Time Pad)](#vernam-cipher-one-time-pad)
4. [Asymmetric Cryptosystems](#asymmetric-cryptosystems)
   - [RSA Cryptosystem (Encryption & Decryption)](#rsa-cryptosystem-encryption--decryption)
   - [RSA Digital Signature Scheme](#rsa-digital-signature-scheme)
   - [ElGamal Cryptosystem (Encryption & Decryption)](#elgamal-cryptosystem-encryption--decryption)
   - [ElGamal Digital Signature Scheme](#elgamal-digital-signature-scheme)
   - [ElGamal Homomorphic Property (Multiplicative)](#elgamal-homomorphic-property-multiplicative)
   - [ElGamal Re-encryption (Proxy / Re-randomization)](#elgamal-re-encryption-proxy--re-randomization)
5. [Elliptic Curve Cryptography (ECC)](#elliptic-curve-cryptography-ecc)
   - [Weierstrass Curve Definition](#weierstrass-curve-definition)
   - [Point Addition & Point Doubling](#point-addition--point-doubling)
   - [Scalar Multiplication (Double-and-Add)](#scalar-multiplication-double-and-add)
   - [ECC Protocols (ECDH, EC-ElGamal, ECDSA)](#ecc-protocols-ecdh-ec-elgamal-ecdsa)
6. [Implementation Audit & Missing Components](#implementation-audit--missing-components)
   - [Bugs Found in Existing Implementations](#bugs-found-in-existing-implementations)
   - [Missing Algorithms (Curriculum / Security Lab Comparison)](#missing-algorithms-curriculum--security-lab-comparison)

---

## Repository Overview

| File | Algorithm / Scheme | Paradigm |
| :--- | :--- | :--- |
| [`ceaser.cpp`](file:///extra/Projects/Security/ceaser.cpp) | Caesar Cipher (Shift Cipher) | Classical Symmetric |
| [`vernam.cpp`](file:///extra/Projects/Security/vernam.cpp) | Vernam Cipher (One-Time Pad / Bitwise XOR) | Classical Symmetric Stream |
| [`rsa.cpp`](file:///extra/Projects/Security/rsa.cpp) | RSA Public-Key Encryption / Decryption | Asymmetric (Integer Factorization) |
| [`rsa-sig.cpp`](file:///extra/Projects/Security/rsa-sig.cpp) | RSA Digital Signature (Sign & Verify) | Digital Signature |
| [`el-gamal.cpp`](file:///extra/Projects/Security/el-gamal.cpp) | ElGamal Encryption & Decryption | Asymmetric (Discrete Logarithm) |
| [`el-gamal-sig.cpp`](file:///extra/Projects/Security/el-gamal-sig.cpp) | ElGamal Digital Signature | Digital Signature |
| [`el-gamal-homo.cpp`](file:///extra/Projects/Security/el-gamal-homo.cpp) | ElGamal Multiplicative Homomorphism | Homomorphic Encryption |
| [`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp) | ElGamal Ciphertext Re-randomization / Re-encryption | Proxy Cryptography |
| [`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp) | Scratchpad / Historical Extended GCD & Discrete Log | Scratchpad |
| [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) | Elliptic Curve Group Operations (Point Add, Double, Multiply) | Asymmetric (ECDLP) |
| [`ecc-key-ex.cpp`](file:///extra/Projects/Security/ecc-key-ex.cpp) | Elliptic Curve Key Exchange (ECDH) | Asymmetric (Incomplete / In-progress) |

---

## Mathematical Foundations & Number Theory

### Extended Euclidean Algorithm & Bézout's Identity
For any integers $a, b \in \mathbb{Z}$, there exist integers $x, y \in \mathbb{Z}$ satisfying Bézout's identity:

$$
a \cdot x + b \cdot y = \gcd(a, b)
$$

**Recursive formulation:**
If $b = 0$, then $\gcd(a, 0) = a$, and $(x, y) = (1, 0)$.  
For $b > 0$, by Euclidean division $a = q \cdot b + r$ where $r = a \pmod b$:

$$
\begin{aligned}
b \cdot x_1 + (a \pmod b) \cdot y_1 &= \gcd(a, b) \\
b \cdot x_1 + \left(a - \left\lfloor \frac{a}{b} \right\rfloor \cdot b\right) \cdot y_1 &= \gcd(a, b) \\
a \cdot y_1 + b \cdot \left(x_1 - \left\lfloor \frac{a}{b} \right\rfloor \cdot y_1\right) &= \gcd(a, b)
\end{aligned}
$$

Thus, the update transitions are:
$$
x = y_1, \quad y = x_1 - \left\lfloor \frac{a}{b} \right\rfloor \cdot y_1
$$

---

### Modular Multiplicative Inverse
An integer $x$ is the modular multiplicative inverse of $a$ modulo $m$ (denoted $a^{-1} \pmod m$) if:

$$
a \cdot x \equiv 1 \pmod m
$$

It exists if and only if $\gcd(a, m) = 1$.

1. **Via Extended Euclidean Algorithm:**
   $$
   a \cdot x + m \cdot y = 1 \implies a \cdot x \equiv 1 \pmod m
   $$
2. **Via Fermat's Little Theorem (when $m = p$ is prime):**
   $$
   a^{p-1} \equiv 1 \pmod p \implies a^{-1} \equiv a^{p-2} \pmod p
   $$
3. **Via Euler's Theorem (general modulus $m$):**
   $$
   a^{\phi(m)} \equiv 1 \pmod m \implies a^{-1} \equiv a^{\phi(m)-1} \pmod m
   $$

---

### Modular Exponentiation (Binary Exponentiation)
Computes $a^e \pmod m$ in $\mathcal{O}(\log e)$ multiplications:

$$
a^e = \prod_{i=0}^{\lfloor \log_2 e \rfloor} a^{2^i \cdot e_i} \pmod m, \quad e_i \in \{0, 1\}
$$

$$
a^e \equiv \begin{cases}
1 \pmod m & \text{if } e = 0 \\
(a^{e/2})^2 \pmod m & \text{if } e \text{ is even} \\
a \cdot (a^{(e-1)/2})^2 \pmod m & \text{if } e \text{ is odd}
\end{cases}
$$

---

### Euler's Totient Function
For $n \in \mathbb{Z}^+$, $\phi(n)$ counts the positive integers up to $n$ relatively prime to $n$:

$$
\phi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right)
$$

For distinct primes $p$ and $q$:
$$
\phi(p) = p - 1, \qquad \phi(n) = \phi(p \cdot q) = (p - 1)(q - 1)
$$

---

### Primitive Roots & Generator Testing
An integer $g$ is a primitive root (generator) modulo a prime $p$ if its multiplicative order equals $p - 1$:

$$
\operatorname{ord}_p(g) = p - 1 \iff \{g^1, g^2, \dots, g^{p-1}\} \equiv \{1, 2, \dots, p - 1\} \pmod p
$$

**Fast criterion:** $g$ is a generator modulo prime $p$ if and only if:
$$
g^{\frac{p-1}{q}} \not\equiv 1 \pmod p \quad \text{for all distinct prime factors } q \text{ of } (p - 1)
$$

---

## Classical Ciphers

### Caesar Cipher
Shift cipher operating over alphabet size $\Sigma$ ($\Sigma = 26$ for letters, $\Sigma = 10$ for digits):

- **Key:** $k \in \mathbb{Z}_\Sigma$
- **Encryption:**
  $$
  C = E(M, k) \equiv (M + k) \pmod \Sigma
  $$
- **Decryption:**
  $$
  M = D(C, k) \equiv (C - k) \pmod \Sigma \equiv (C - k + \Sigma) \pmod \Sigma
  $$

---

### Vernam Cipher (One-Time Pad)
Stream cipher utilizing bitwise exclusive-OR ($\oplus$):

- **Plaintext bit vector:** $M = (m_1, m_2, \dots, m_n), \; m_i \in \{0, 1\}$
- **Key bit vector:** $K = (k_1, k_2, \dots, k_n), \; k_i \in \{0, 1\}$ with $|K| = |M|$
- **Encryption:**
  $$
  c_i = m_i \oplus k_i
  $$
- **Decryption:**
  $$
  m_i = c_i \oplus k_i = (m_i \oplus k_i) \oplus k_i = m_i \oplus (k_i \oplus k_i) = m_i \oplus 0 = m_i
  $$

**Information-Theoretic Security Condition (Shannon):**  
If $K$ is truly uniform, $|K| \ge |M|$, and $K$ is never reused, then $H(M \mid C) = H(M)$ (perfect secrecy).

---

## Asymmetric Cryptosystems

### RSA Cryptosystem (Encryption & Decryption)

#### 1. Key Generation
1. Choose two large distinct primes $p$ and $q$.
2. Compute the RSA modulus:
   $$
   n = p \cdot q
   $$
3. Compute Euler's totient:
   $$
   \phi(n) = (p - 1)(q - 1)
   $$
4. Choose public exponent $e$ such that:
   $$
   1 < e < \phi(n) \quad \text{and} \quad \gcd(e, \phi(n)) = 1
   $$
5. Compute private exponent $d$:
   $$
   d \equiv e^{-1} \pmod{\phi(n)} \iff e \cdot d \equiv 1 \pmod{\phi(n)}
   $$
- **Public Key:** $(e, n)$  
- **Private Key:** $(d, n)$ or $(p, q, d)$

#### 2. Encryption
Given plaintext message $m \in \mathbb{Z}_n$:
$$
c \equiv m^e \pmod n
$$

#### 3. Decryption
Given ciphertext $c \in \mathbb{Z}_n$:
$$
m \equiv c^d \pmod n
$$

#### Proof of Correctness
Since $e \cdot d \equiv 1 \pmod{\phi(n)}$, there exists $k \in \mathbb{Z}$ such that $e \cdot d = 1 + k \cdot \phi(n)$.  
By Euler's Theorem, for $\gcd(m, n) = 1$:
$$
c^d \equiv (m^e)^d \equiv m^{ed} \equiv m^{1 + k\phi(n)} \equiv m \cdot (m^{\phi(n)})^k \equiv m \cdot 1^k \equiv m \pmod n
$$

---

### RSA Digital Signature Scheme

#### 1. Signing
Signer uses their private key $d$ to sign message $m$ (or hash $H(m)$):
$$
s \equiv m^d \pmod n
$$

#### 2. Verification
Verifier uses the signer's public key $(e, n)$ to compute:
$$
v \equiv s^e \pmod n
$$
The signature is **valid** if and only if:
$$
v = m \quad (\text{or } v = H(m))
$$

---

### ElGamal Cryptosystem (Encryption & Decryption)

#### 1. Key Generation
1. Select a large prime $p$ and a primitive root $g \pmod p$.
2. Choose private key $x$ (or $a$) uniformly at random:
   $$
   x \in \{2, 3, \dots, p - 2\}
   $$
3. Compute the public key $y$:
   $$
   y \equiv g^x \pmod p
   $$
- **Public Parameters:** $(p, g)$
- **Public Key:** $y$
- **Private Key:** $x$

#### 2. Encryption
To encrypt message $m \in \{1, 2, \dots, p - 1\}$:
1. Choose an ephemeral random key $k \in \{2, 3, \dots, p - 2\}$ such that $\gcd(k, p - 1) = 1$.
2. Compute the ciphertext pair $(c_1, c_2)$:
   $$
   \begin{aligned}
   c_1 &\equiv g^k \pmod p \\
   c_2 &\equiv m \cdot y^k \pmod p
   \end{aligned}
   $$

#### 3. Decryption
To decrypt ciphertext $(c_1, c_2)$ using private key $x$:
1. Compute the shared secret:
   $$
   s \equiv c_1^x \equiv (g^k)^x \equiv g^{kx} \equiv y^k \pmod p
   $$
2. Recover plaintext $m$ by multiplying $c_2$ with the modular inverse of $s$:
   $$
   m \equiv c_2 \cdot s^{-1} \equiv c_2 \cdot (c_1^x)^{-1} \pmod p
   $$
   Equivalently via Fermat's Little Theorem:
   $$
   m \equiv c_2 \cdot c_1^{p - 1 - x} \pmod p
   $$

---

### ElGamal Digital Signature Scheme

#### 1. Signing
To sign message $m \in \mathbb{Z}_{p-1}$:
1. Choose random ephemeral key $k \in \{1, 2, \dots, p - 2\}$ such that $\gcd(k, p - 1) = 1$.
2. Compute $s_1$ (or $c_1$):
   $$
   s_1 \equiv g^k \pmod p
   $$
3. Compute $s_2$ (or $c_2$):
   $$
   s_2 \equiv k^{-1} \cdot (m - x \cdot s_1) \pmod{p - 1}
   $$
- **Signature:** $(s_1, s_2)$

#### 2. Verification
Given message $m$, public key $y$, and signature $(s_1, s_2)$:
1. Verify $1 \le s_1 < p$ and $0 \le s_2 < p - 1$.
2. Check the verification congruence:
   $$
   v_1 \equiv y^{s_1} \cdot s_1^{s_2} \pmod p
   $$
   $$
   v_2 \equiv g^m \pmod p
   $$
The signature is **valid** if and only if $v_1 \equiv v_2 \pmod p$.

#### Proof of Correctness
$$
y^{s_1} s_1^{s_2} \equiv (g^x)^{s_1} (g^k)^{k^{-1}(m - x s_1)} \equiv g^{x s_1} \cdot g^{m - x s_1} \equiv g^{x s_1 + m - x s_1} \equiv g^m \pmod p
$$

---

### ElGamal Homomorphic Property (Multiplicative)
ElGamal is **multiplicatively homomorphic**. Given two ciphertexts encrypted under the same public key $y$:

$$
C(m_1) = (c_1, c_2) = (g^{k_1} \bmod p, \; m_1 y^{k_1} \bmod p)
$$
$$
C(m_2) = (c_1', c_2') = (g^{k_2} \bmod p, \; m_2 y^{k_2} \bmod p)
$$

Component-wise modular multiplication yields:
$$
C_{\text{mult}} = (c_{1,\text{new}}, c_{2,\text{new}}) = (c_1 \cdot c_1' \bmod p, \; c_2 \cdot c_2' \bmod p)
$$

$$
\begin{aligned}
c_{1,\text{new}} &\equiv g^{k_1} \cdot g^{k_2} \equiv g^{k_1 + k_2} \pmod p \\
c_{2,\text{new}} &\equiv (m_1 y^{k_1}) \cdot (m_2 y^{k_2}) \equiv (m_1 \cdot m_2) \cdot y^{k_1 + k_2} \pmod p
\end{aligned}
$$

Decrypting $C_{\text{mult}}$:
$$
D(C_{\text{mult}}) \equiv c_{2,\text{new}} \cdot (c_{1,\text{new}}^x)^{-1} \equiv (m_1 \cdot m_2) \pmod p
$$

---

### ElGamal Re-encryption (Proxy / Re-randomization)
A ciphertext $(c_1, c_2)$ can be re-randomized into a fresh ciphertext $(c_1', c_2')$ **without decrypting** and **without knowing the private key $x$**:

1. Choose fresh random integer $k' \in \mathbb{Z}_{p-1}$.
2. Compute:
   $$
   c_1' \equiv c_1 \cdot g^{k'} \equiv g^k \cdot g^{k'} \equiv g^{k + k'} \pmod p
   $$
   $$
   c_2' \equiv c_2 \cdot y^{k'} \equiv (m \cdot y^k) \cdot y^{k'} \equiv m \cdot y^{k + k'} \pmod p
   $$
3. Decryption with private key $x$:
   $$
   m \equiv c_2' \cdot (c_1'^x)^{-1} \equiv m \cdot y^{k + k'} \cdot (g^{(k + k')x})^{-1} \equiv m \pmod p
   $$

---

## Elliptic Curve Cryptography (ECC)

### Weierstrass Curve Definition
An elliptic curve $E$ over a finite field $\mathbb{F}_p$ ($p > 3$) in short Weierstrass form is:

$$
E(\mathbb{F}_p): y^2 \equiv x^3 + ax + b \pmod p
$$

with parameters $a, b \in \mathbb{F}_p$ satisfying the non-singularity condition (non-zero discriminant):

$$
\Delta = -16(4a^3 + 27b^2) \not\equiv 0 \pmod p \iff 4a^3 + 27b^2 \not\equiv 0 \pmod p
$$

The set of points on the curve forms an abelian group:
$$
E(\mathbb{F}_p) = \{(x, y) \in \mathbb{F}_p \times \mathbb{F}_p \mid y^2 \equiv x^3 + ax + b \pmod p\} \cup \{\mathcal{O}\}
$$
where $\mathcal{O}$ is the point at infinity (identity element).

#### Finding Valid Curve Points (Modular Square Root / `Space::operator()`)
Given an $x$-coordinate, the corresponding $y$-coordinate satisfies:
$$
y^2 \equiv \text{rhs} \equiv (x^3 + ax + b) \pmod p
$$
Unlike real numbers, finite field arithmetic does **not** use real floating-point $\sqrt{\cdot}$. Instead:
1. **Euler's Criterion (Solvability Test):**  
   A point exists with coordinate $x$ if and only if:
   $$
   \text{rhs}^{\frac{p-1}{2}} \equiv 1 \pmod p \quad (\text{or } \text{rhs} \equiv 0 \pmod p)
   $$
   If $\text{rhs}^{(p-1)/2} \equiv -1 \equiv p - 1 \pmod p$, then $\text{rhs}$ is a quadratic non-residue, and **no such point exists on the curve**.
2. **Finding $y$ for $p \equiv 3 \pmod 4$:**
   $$
   y \equiv \text{rhs}^{\frac{p+1}{4}} \pmod p
   $$
3. **Finding $y$ via Search (Small finite fields):**
   $$
   \text{Find } y \in \{0, 1, \dots, p - 1\} \quad \text{such that} \quad y^2 \equiv \text{rhs} \pmod p
   $$
   If a solution $y$ exists, its symmetric counterpart is $-y \equiv p - y \pmod p$.

---

### Point Addition & Point Doubling

#### 1. Identity Rules
For any point $P = (x_1, y_1)$:
$$
P + \mathcal{O} = \mathcal{O} + P = P
$$
$$
P + (-P) = \mathcal{O}, \quad \text{where } -P = (x_1, -y_1 \bmod p) = (x_1, p - y_1)
$$

#### 2. Point Addition ($P \ne Q$, $x_1 \ne x_2$)
For distinct points $P = (x_1, y_1)$ and $Q = (x_2, y_2)$:
$$
\lambda \equiv \frac{y_2 - y_1}{x_2 - x_1} \pmod p
$$
$$
x_3 \equiv \lambda^2 - x_1 - x_2 \pmod p
$$
$$
y_3 \equiv \lambda(x_1 - x_3) - y_1 \pmod p
$$

#### 3. Point Doubling ($P = Q$)
For $P = (x_1, y_1)$:
- If $y_1 \equiv 0 \pmod p$, then $2P = \mathcal{O}$ (tangent line is vertical).
- Otherwise, slope of the tangent:
  $$
  \lambda \equiv \frac{3x_1^2 + a}{2y_1} \pmod p
  $$
  $$
  x_3 \equiv \lambda^2 - 2x_1 \pmod p
  $$
  $$
  y_3 \equiv \lambda(x_1 - x_3) - y_1 \pmod p
  $$

---

### Scalar Multiplication (Double-and-Add)
Computes $Q = kP = \underbrace{P + P + \dots + P}_{k \text{ times}}$ in $\mathcal{O}(\log k)$ point additions:

Let $k = \sum_{i=0}^{\lfloor \log_2 k \rfloor} k_i 2^i$ with $k_i \in \{0, 1\}$.

```
R = O (Point at Infinity)
T = P
while k > 0:
    if k & 1:
        R = R + T
    T = T + T   # Double
    k >>= 1     # Shift right
return R
```

---

### ECC Protocols (ECDH, EC-ElGamal, ECDSA)

#### 1. ECDH (Elliptic Curve Diffie-Hellman Key Exchange)
- **Domain Parameters:** Curve $E(\mathbb{F}_p)$, base point $G$ of prime order $n$.
- Alice selects private key $d_A \in [1, n-1]$, sends public key $Q_A = d_A G$.
- Bob selects private key $d_B \in [1, n-1]$, sends public key $Q_B = d_B G$.
- **Shared Secret:**
  $$
  K = d_A Q_B = d_A (d_B G) = d_B (d_A G) = d_B Q_A
  $$

#### 2. EC-ElGamal (Elliptic Curve Encryption)
- Plaintext embedded as a curve point $P_m \in E(\mathbb{F}_p)$.
- Receiver public key: $Q = dG$ ($d$ is private).
- **Encryption:** Choose random $k \in [1, n-1]$:
  $$
  C_1 = kG, \qquad C_2 = P_m + kQ
  $$
- **Decryption:**
  $$
  P_m = C_2 - dC_1 = (P_m + kQ) - d(kG) = P_m + k(dG) - k(dG) = P_m
  $$

#### 3. ECDSA (Elliptic Curve Digital Signature Algorithm)
- Private key $d$, Public key $Q = dG$, message hash $z = H(m)$.
- **Signing:**
  1. Pick random $k \in [1, n-1]$.
  2. Compute $(x_1, y_1) = kG$.
  3. $r = x_1 \pmod n$ (if $r = 0$, retry).
  4. $s \equiv k^{-1}(z + r \cdot d) \pmod n$ (if $s = 0$, retry).
  5. Signature: $(r, s)$.
- **Verification:**
  1. Verify $r, s \in [1, n-1]$.
  2. $w \equiv s^{-1} \pmod n$.
  3. $u_1 \equiv z \cdot w \pmod n, \quad u_2 \equiv r \cdot w \pmod n$.
  4. Compute point $(x_1, y_1) = u_1 G + u_2 Q$.
  5. Valid if and only if $r \equiv x_1 \pmod n$.

---

## Implementation Audit & Missing Components

### Implementation Status & Audit

#### Resolved Fixes
- [x] **[`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp):** Scalar multiplication exponent loop fixed from `t--` to `t >>= 1`.
- [x] **[`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp):** `Space::operator()` updated from floating-point `sqrt` to finite field search $y^2 \equiv (x^3 + ax + b) \pmod p$.
- [x] **[`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp):** Inverted infinity condition corrected to `if ((y + t.y) % s.p == 0) return Point<s>();`.
- [x] **[`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp):** Extended Euclidean parameter order fixed from `b%a` to `a%b`.
- [x] **[`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp):** Re-randomization exponent changed from `k` to fresh randomness `k_` for computing `c1_` and `c2_`.

#### Remaining Issues to Address

| File | Location | Issue | Required Fix |
| :--- | :--- | :--- | :--- |
| [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) | L14-15 | **Negative RHS in `operator()`:** If $x^3 + ax + b < 0$, `rhs % p` is negative in C++. | Wrap with `rhs = (rhs % p + p) % p;`. |
| [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) | L55-56, L74-75 | **Negative coordinates:** `x3` and `y3` can be negative before modulo. `Point` constructor uses `% s.p` which preserves negative sign. | Use `mod(x, s.p)` and `mod(y, s.p)`. |
| [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) | L106 | **Composite modulus in test:** $p = 9$ is composite; Fermat's inverse $a^{p-2}$ fails in `modinv`. | Test with prime $p$ (e.g. $p = 17, a = 1, b = 2$). |
| [`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp) | L78 | **Decryption target:** `dec_` decrypts `c2` and `c1` instead of `c2_` and `c1_`. | Change to `mod_mul(c2_, mod_inv(mod_pow(c1_, a, p), p), p)`. |
| [`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp) | L79-80 | **Missing return statement:** `extended_gcd` does not return `g` on the recursive branch. | Add `return g;`. |
| [`ecc-key-ex.cpp`](file:///extra/Projects/Security/ecc-key-ex.cpp) | Whole file | **Incomplete file:** File contains only 10 lines (stub). | Implement ECDH key exchange ($Q_A = d_A G, Q_B = d_B G, K = d_A Q_B = d_B Q_A$). |
| [`ceaser.cpp`](file:///extra/Projects/Security/ceaser.cpp) | L19-23 | Negative modulo underflow if shift key $k > 26$: `26 + (c - 'a' - k)` can remain negative. | Use `((c - 'a' - k) % 26 + 26) % 26`. |

---

### Missing Algorithms (Curriculum / Security Lab Comparison)

Compared to standard university Network Security / Cryptography curricula (e.g., KUET, BUET, or Stallings' *Cryptography and Network Security*):

#### 1. Classical Ciphers Still Missing
- **Playfair Cipher:** $5 \times 5$ key matrix encrypting digraphs (pairs of letters) with row/column/rectangle swap rules.
- **Hill Cipher:** Linear algebra polygraphic cipher: $C \equiv M \cdot K \pmod{26}$, requiring matrix invertibility ($\gcd(\det(K), 26) = 1$).
- **Vigenère Cipher:** Polyalphabetic substitution repeating key stream: $c_i = (m_i + k_{i \bmod |k|}) \pmod{26}$.
- **Transposition Ciphers:** Rail Fence Cipher, Columnar / Row Transposition.

#### 2. Key Exchange & Public Key Schemes Still Missing
- **Diffie-Hellman Key Exchange (DHKE):** Alice & Bob exchange $g^a \bmod p$ and $g^b \bmod p$ to derive shared key $K = g^{ab} \bmod p$.
- **Full ECC Schemes:** `ecc.cpp` has point addition/doubling, but lacks:
  - ECDH (Elliptic Curve Diffie-Hellman).
  - EC-ElGamal (Encryption & Decryption using point masking).
  - ECDSA (Elliptic Curve Digital Signature Algorithm).
- **Paillier Cryptosystem:** Additively homomorphic cryptosystem ($D(c_1 \cdot c_2 \bmod n^2) = m_1 + m_2 \bmod n$), commonly taught alongside ElGamal multiplicative homomorphism.

#### 3. Modern Symmetric Block Ciphers Still Missing
- **Simplified DES (S-DES):** 8-bit block, 10-bit key, 2 rounds with P10, P8, IP, EP, S-boxes (S0, S1), P4, and SW.
- **Simplified AES (S-AES):** 16-bit block, 16-bit key, 2 rounds with NibbleSub, ShiftRow, MixColumn, and AddRoundKey over $\text{GF}(2^4)$.
- **Modes of Operation:** ECB, CBC, CFB, OFB, CTR.

#### 4. Cryptographic Hash Functions & MAC Still Missing
- **Toy Merkle-Damgård / MD5 / SHA-1 / SHA-256:** Compression functions, bitwise operations, padding.
- **HMAC:** Keyed-hash construction $\text{HMAC}(K, M) = H((K \oplus opad) \parallel H((K \oplus ipad) \parallel M))$.

#### 5. Mathematical Primitives Still Missing
- **Miller-Rabin Primality Test:** Probabilistic test checking $a^d \equiv 1 \pmod p$ and $a^{2^r d} \equiv -1 \pmod p$.
- **Chinese Remainder Theorem (CRT):** Speeding up RSA private key operations ($d_p = d \bmod (p-1)$, $d_q = d \bmod (q-1)$).
- **Discrete Log Solvers (Attacks):** Baby-step Giant-step algorithm ($\mathcal{O}(\sqrt{p})$).
