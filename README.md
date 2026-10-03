# Cryptography & Security — Formula Cheatsheet

> [!NOTE]
> **AI Disclosure:** This `README.md` cheatsheet is **AI-generated**.  
> All source code implementations (`*.cpp`) in this repository are **handwritten and human-crafted**.

---

## Repository Map

| Type | Algorithm | Source File |
| :--- | :--- | :--- |
| **Classical** | Caesar Cipher | [`ceaser.cpp`](file:///extra/Projects/Security/ceaser.cpp) |
| **Classical** | Vernam Cipher (OTP) | [`vernam.cpp`](file:///extra/Projects/Security/vernam.cpp) |
| **Foundations** | Extended Euclidean Algorithm & Inverse | [`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp) |
| **Asymmetric** | RSA Encryption & Decryption | [`rsa.cpp`](file:///extra/Projects/Security/rsa.cpp) |
| **Asymmetric** | RSA Digital Signature | [`rsa-sig.cpp`](file:///extra/Projects/Security/rsa-sig.cpp) |
| **Asymmetric** | ElGamal Encryption & Decryption | [`el-gamal.cpp`](file:///extra/Projects/Security/el-gamal.cpp) |
| **Asymmetric** | ElGamal Digital Signature | [`el-gamal-sig.cpp`](file:///extra/Projects/Security/el-gamal-sig.cpp) |
| **Asymmetric** | ElGamal Homomorphic Multiplication | [`el-gamal-homo.cpp`](file:///extra/Projects/Security/el-gamal-homo.cpp) |
| **Asymmetric** | ElGamal Re-encryption | [`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp) |
| **ECC** | Elliptic Curve Group Operations | [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) |
| **ECC** | ECDH Key Exchange | [`ecc-key-ex.cpp`](file:///extra/Projects/Security/ecc-key-ex.cpp) |
| **ECC** | EC-ElGamal Encryption & Decryption | [`ecc-enc.cpp`](file:///extra/Projects/Security/ecc-enc.cpp) |

---

## 1. Classical Ciphers

### Caesar Cipher ([`ceaser.cpp`](file:///extra/Projects/Security/ceaser.cpp))

$$
\text{Alphabet Size: } \Sigma = 26 \text{ (letters)}, \quad \Sigma = 10 \text{ (digits)}, \quad k \in \mathbb{Z}_\Sigma
$$

$$
\begin{aligned}
\text{Encryption:} \quad C &= (M + k) \pmod \Sigma \\
\text{Decryption:} \quad M &= (C - k + \Sigma) \pmod \Sigma
\end{aligned}
$$

---

### Vernam Cipher / One-Time Pad ([`vernam.cpp`](file:///extra/Projects/Security/vernam.cpp))

$$
M = (m_1, m_2, \dots, m_n), \quad K = (k_1, k_2, \dots, k_n), \quad m_i, k_i \in \{0, 1\}, \quad |K| = |M|
$$

$$
\begin{aligned}
\text{Encryption:} \quad c_i &= m_i \oplus k_i \\
\text{Decryption:} \quad m_i &= c_i \oplus k_i = (m_i \oplus k_i) \oplus k_i = m_i
\end{aligned}
$$

$$
\text{Perfect Secrecy (Shannon): } H(M \mid C) = H(M) \iff K \text{ is uniform, } |K| \ge |M|, \text{ used once}
$$

---

## 2. Number Theory Foundations

### Extended Euclidean Algorithm ([`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp))

$$
a \cdot x + b \cdot y = \gcd(a, b)
$$

$$
\begin{aligned}
\text{Base Case } (b = 0): \quad & \gcd(a, 0) = a, \quad x = 1, \quad y = 0 \\
\text{Step } (b > 0): \quad & x = y_1, \quad y = x_1 - \left\lfloor \frac{a}{b} \right\rfloor \cdot y_1
\end{aligned}
$$

---

### Modular Multiplicative Inverse

$$
a \cdot x \equiv 1 \pmod m \iff \gcd(a, m) = 1
$$

$$
\begin{aligned}
\text{Extended GCD:} \quad & a \cdot x + m \cdot y = 1 \implies x \equiv a^{-1} \pmod m \\
\text{Fermat's Little Theorem } (m = p \text{ prime}): \quad & a^{-1} \equiv a^{p-2} \pmod p \\
\text{Euler's Theorem } (\text{general } m): \quad & a^{-1} \equiv a^{\phi(m)-1} \pmod m
\end{aligned}
$$

---

### Modular Exponentiation (Square-and-Multiply)

$$
a^e \pmod m, \quad e = \sum_{i=0}^{\lfloor \log_2 e \rfloor} e_i 2^i, \quad e_i \in \{0, 1\}
$$

$$
a^e \equiv \begin{cases}
1 \pmod m & e = 0 \\
(a^{e/2})^2 \pmod m & e \text{ even} \\
a \cdot (a^{(e-1)/2})^2 \pmod m & e \text{ odd}
\end{cases}
$$

---

### Euler's Totient Function $\phi(n)$

$$
\phi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right)
$$

$$
\phi(p) = p - 1, \qquad \phi(p \cdot q) = (p - 1)(q - 1) \quad (p \ne q \text{ primes})
$$

---

### Primitive Root / Generator Testing

$$
g \text{ is primitive root modulo } p \iff \mathrm{ord}_p(g) = p - 1
$$

$$
g^{\frac{p-1}{q}} \not\equiv 1 \pmod p \quad \text{for all prime factors } q \text{ of } (p - 1)
$$

---

## 3. RSA Cryptosystem

### RSA Encryption & Decryption ([`rsa.cpp`](file:///extra/Projects/Security/rsa.cpp))

$$
\begin{aligned}
\text{Key Generation:} \quad & n = p \cdot q \\
& \phi(n) = (p - 1)(q - 1) \\
& \gcd(e, \phi(n)) = 1, \quad 1 \lt e \lt \phi(n) \\
& d \equiv e^{-1} \pmod{\phi(n)} \\
\text{Public Key:} \quad & (e, n) \\
\text{Private Key:} \quad & (d, n)
\end{aligned}
$$

$$
\begin{aligned}
\text{Encryption:} \quad & c \equiv m^e \pmod n \\
\text{Decryption:} \quad & m \equiv c^d \pmod n
\end{aligned}
$$

$$
\text{Correctness: } c^d \equiv (m^e)^d \equiv m^{ed} \equiv m^{1 + k\phi(n)} \equiv m \cdot (m^{\phi(n)})^k \equiv m \pmod n
$$

---

### RSA Digital Signature ([`rsa-sig.cpp`](file:///extra/Projects/Security/rsa-sig.cpp))

$$
\begin{aligned}
\text{Sign (Private } d\text{):} \quad & s \equiv m^d \pmod n \\
\text{Verify (Public } e\text{):} \quad & v \equiv s^e \pmod n \\
\text{Validation:} \quad & v \equiv m \iff \text{Valid Signature}
\end{aligned}
$$

---

## 4. ElGamal Cryptosystem

### ElGamal Encryption & Decryption ([`el-gamal.cpp`](file:///extra/Projects/Security/el-gamal.cpp))

$$
\begin{aligned}
\text{Public Domain:} \quad & p \text{ (prime)}, \quad g \text{ (generator } \!\bmod p) \\
\text{Key Generation:} \quad & x \in [2, p - 2] \quad (\text{Private}), \quad y \equiv g^x \pmod p \quad (\text{Public}) \\
\text{Encryption:} \quad & k \in [2, p - 2], \quad \gcd(k, p - 1) = 1 \\
& c_1 \equiv g^k \pmod p \\
& c_2 \equiv m \cdot y^k \pmod p \\
\text{Ciphertext:} \quad & (c_1, c_2) \\
\text{Decryption:} \quad & s \equiv c_1^x \equiv (g^k)^x \equiv y^k \pmod p \\
& m \equiv c_2 \cdot s^{-1} \equiv c_2 \cdot c_1^{p - 1 - x} \pmod p
\end{aligned}
$$

---

### ElGamal Digital Signature ([`el-gamal-sig.cpp`](file:///extra/Projects/Security/el-gamal-sig.cpp))

$$
\begin{aligned}
\text{Sign (Private } x\text{):} \quad & k \in [1, p - 2], \quad \gcd(k, p - 1) = 1 \\
& s_1 \equiv g^k \pmod p \\
& s_2 \equiv k^{-1} (m - x \cdot s_1) \pmod{p - 1} \\
\text{Signature:} \quad & (s_1, s_2)
\end{aligned}
$$

$$
\begin{aligned}
\text{Verify (Public } y\text{):} \quad & 1 \le s_1 \lt p \\
& v_1 \equiv y^{s_1} \cdot s_1^{s_2} \pmod p \\
& v_2 \equiv g^m \pmod p \\
\text{Validation:} \quad & v_1 \equiv v_2 \iff \text{Valid Signature}
\end{aligned}
$$

$$
\text{Proof: } y^{s_1} s_1^{s_2} \equiv (g^x)^{s_1} (g^k)^{k^{-1}(m - x s_1)} \equiv g^{x s_1 + m - x s_1} \equiv g^m \pmod p
$$

---

### ElGamal Multiplicative Homomorphism ([`el-gamal-homo.cpp`](file:///extra/Projects/Security/el-gamal-homo.cpp))

$$
C(m_1) = (g^{k_1}, m_1 y^{k_1}), \qquad C(m_2) = (g^{k_2}, m_2 y^{k_2})
$$

$$
\begin{aligned}
C_{\text{mult}} &= (c_1 \cdot c_1' \bmod p, \; c_2 \cdot c_2' \bmod p) \\
&= (g^{k_1 + k_2} \bmod p, \; (m_1 \cdot m_2) y^{k_1 + k_2} \bmod p)
\end{aligned}
$$

$$
D(C_{\text{mult}}) \equiv c_{2,\text{mult}} \cdot (c_{1,\text{mult}}^x)^{-1} \equiv m_1 \cdot m_2 \pmod p
$$

---

### ElGamal Re-encryption / Re-randomization ([`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp))

$$
(c_1, c_2) = (g^k \bmod p, \; m y^k \bmod p), \quad k' \in \mathbb{Z}_{p-1} \text{ (fresh randomness)}
$$

$$
\begin{aligned}
c_1' &\equiv c_1 \cdot g^{k'} \equiv g^{k + k'} \pmod p \\
c_2' &\equiv c_2 \cdot y^{k'} \equiv m \cdot y^{k + k'} \pmod p
\end{aligned}
$$

$$
D(c_1', c_2') \equiv c_2' \cdot (c_1'^x)^{-1} \equiv m \pmod p
$$

---

## 5. Elliptic Curve Cryptography (ECC)

### Weierstrass Form & Discriminant

$$
E(\mathbb{F}_p): y^2 \equiv x^3 + ax + b \pmod p, \quad p \gt 3
$$

$$
\Delta = 4a^3 + 27b^2 \not\equiv 0 \pmod p \quad (\text{Non-singularity})
$$

---

### Finding Curve Points & Modular Square Root

$$
y^2 \equiv \text{rhs} \equiv (x^3 + ax + b) \pmod p
$$

$$
\begin{aligned}
\text{Euler's Criterion:} \quad & \text{rhs}^{\frac{p-1}{2}} \equiv 1 \pmod p \iff y \text{ exists} \\
\text{For } p \equiv 3 \pmod 4: \quad & y \equiv \text{rhs}^{\frac{p+1}{4}} \pmod p \\
\text{Symmetric Point:} \quad & -P = (x, -y \bmod p) = (x, p - y)
\end{aligned}
$$

---

### Point Addition ($P \ne Q$)

$$
P = (x_1, y_1), \quad Q = (x_2, y_2), \quad x_1 \ne x_2
$$

$$
\begin{aligned}
\lambda &\equiv \frac{y_2 - y_1}{x_2 - x_1} \pmod p \\
x_3 &\equiv \lambda^2 - x_1 - x_2 \pmod p \\
y_3 &\equiv \lambda(x_1 - x_3) - y_1 \pmod p
\end{aligned}
$$

---

### Point Doubling ($P = Q$)

$$
P = (x_1, y_1), \quad y_1 \ne 0
$$

$$
\begin{aligned}
\lambda &\equiv \frac{3x_1^2 + a}{2y_1} \pmod p \\
x_3 &\equiv \lambda^2 - 2x_1 \pmod p \\
y_3 &\equiv \lambda(x_1 - x_3) - y_1 \pmod p
\end{aligned}
$$

$$
\text{If } y_1 \equiv 0 \pmod p \implies 2P = \mathcal{O} \quad (\text{Point at Infinity})
$$

---

### Identity & Group Rules

$$
P + \mathcal{O} = \mathcal{O} + P = P, \qquad P + (-P) = \mathcal{O}
$$

---

### Scalar Multiplication (Double-and-Add)

$$
kP = \underbrace{P + P + \dots + P}_{k \text{ times}}, \quad k = \sum_{i=0}^{\lfloor \log_2 k \rfloor} k_i 2^i, \quad k_i \in \{0, 1\}
$$

$$
R = \mathcal{O}, \quad T = P; \quad \forall i: \quad (\text{if } k_i = 1 \implies R = R + T), \quad T = 2T
$$

---

### ECDH: Elliptic Curve Diffie-Hellman ([`ecc-key-ex.cpp`](file:///extra/Projects/Security/ecc-key-ex.cpp))

$$
\begin{aligned}
\text{Domain:} \quad & E(\mathbb{F}_p), \quad G \text{ (Base Point)}, \quad n = \mathrm{ord}(G) \\
\text{Alice:} \quad & d_A \in [1, n-1] \quad (\text{Private}), \quad Q_A = d_A G \quad (\text{Public}) \\
\text{Bob:} \quad & d_B \in [1, n-1] \quad (\text{Private}), \quad Q_B = d_B G \quad (\text{Public}) \\
\text{Shared Secret:} \quad & K = d_A Q_B = d_A(d_B G) = d_B(d_A G) = d_B Q_A
\end{aligned}
$$

---

### EC-ElGamal: Encryption & Decryption ([`ecc-enc.cpp`](file:///extra/Projects/Security/ecc-enc.cpp))

$$
\begin{aligned}
\text{KeyGen:} \quad & d \in [1, n-1] \quad (\text{Private}), \quad Q = dG \quad (\text{Public}) \\
\text{Encrypt:} \quad & M \in E(\mathbb{F}_p), \quad k \in [1, n-1] \\
& C_1 = kG \\
& C_2 = M + kQ \\
\text{Ciphertext:} \quad & (C_1, C_2) \\
\text{Decrypt:} \quad & M = C_2 - dC_1 = (M + kdG) - d(kG) = M
\end{aligned}
$$

---

### ECDSA: Digital Signature Algorithm

$$
\begin{aligned}
\text{KeyGen:} \quad & d \in [1, n-1] \quad (\text{Private}), \quad Q = dG \quad (\text{Public}) \\
\text{Sign:} \quad & z = H(m), \quad k \in [1, n-1] \\
& (x_1, y_1) = kG \\
& r = x_1 \pmod n \quad (r \ne 0) \\
& s \equiv k^{-1}(z + r \cdot d) \pmod n \quad (s \ne 0) \\
\text{Signature:} \quad & (r, s)
\end{aligned}
$$

$$
\begin{aligned}
\text{Verify:} \quad & w \equiv s^{-1} \pmod n \\
& u_1 \equiv z \cdot w \pmod n, \quad u_2 \equiv r \cdot w \pmod n \\
& (x_1, y_1) = u_1 G + u_2 Q \\
\text{Validation:} \quad & r \equiv x_1 \pmod n \iff \text{Valid Signature}
\end{aligned}
$$

---

## 6. Implementation Audit

### Resolved Implementations & Bug Fixes
- [x] **[`ecc-enc.cpp`](file:///extra/Projects/Security/ecc-enc.cpp):** Implemented EC-ElGamal encryption and decryption ($C_1 = kG, C_2 = M + kQ, M = C_2 - dC_1$).
- [x] **[`ecc-key-ex.cpp`](file:///extra/Projects/Security/ecc-key-ex.cpp):** Implemented ECDH key exchange ($K = d_A Q_B = d_B Q_A$), fixed $x$ variable shadowing, negative modulo, and $4a^3$ discriminant check.
- [x] **[`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp):** Fixed scalar multiplication exponent loop (`t >>= 1`), finite field modular square root search in `Space::operator()`, corrected point doubling infinity condition `(y + t.y) % p == 0`, and added `den == 0` guard.
- [x] **[`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp):** Fixed parameter order in `extended_gcd(b, a%b, ...)`.
- [x] **[`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp):** Re-randomization exponent updated to fresh randomness `k_`.

### Remaining Minor Fixes

| File | Location | Issue | Fix |
| :--- | :--- | :--- | :--- |
| [`el-gamal-re.cpp`](file:///extra/Projects/Security/el-gamal-re.cpp) | L78 | `dec_` decrypts `c2, c1` instead of `c2_, c1_`. | Change to `mod_mul(c2_, mod_inv(mod_pow(c1_, a, p), p), p)`. |
| [`ecc.cpp`](file:///extra/Projects/Security/ecc.cpp) | L14-15 | `(x*x*x + a*x + b) % p` can be negative in C++. | Wrap with `(rhs % p + p) % p`. |
| [`al-jamal.cpp`](file:///extra/Projects/Security/al-jamal.cpp) | L79-80 | Missing `return g;` in `extended_gcd`. | Add `return g;`. |
| [`ceaser.cpp`](file:///extra/Projects/Security/ceaser.cpp) | L19-23 | Negative modulo underflow if shift key $k > 26$. | Use `((c - 'a' - k) % 26 + 26) % 26`. |
