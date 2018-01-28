## CryptoCipher

### Part 1: Establishment of a shared session key K A,B between the client A and the server B. For this part, we use the Diffie-Hellman key exchange protocol, which is described below:

#### Global Public Elements

• q : a sufficiently large prime, such that it is intractable to compute
the discrete logarithms in Z_q ∗ .

• α : α < q and α a primitive root of q.

#### User A Key Generation

• Select private X_a such that X_a < q

• Calculate public Y A such that Y_a= α ^(X_a) mod q

A → B : {Y_a, q, α}

Here A → B : M denotes party A sends a message M to party B.

#### User B Key Generation

• Select private X B such that X B < q

• Calculate public Y B such that Y B = α ^(X_b) mod q

B → A : {Y_b }


#### Generation of secret key by User A

• Compute the shared key with B as K A,B = (Y B ) X A mod q

#### Generation of secret key by User B

• Compute the shared key with A as K B,A = (Y A ) X B mod q = K A,B


### Part 2: Implementation of Generalized Caesar Cipher using the Established Key in Part 1.


#### Alice (client A) encrypts the plaintext, say, This is 2018! using a key k = K (mod 66), and sends the ciphertext to Bob (server B). Bob B will decrypt the ciphertext.

#### Bob (server B) encrypts the plaintext, say, Meet me after the party at 10 P.M. night at IIIT felicity ground. using a key k = K (mod 66), and sends the ciphertext to Alice (client A). A will decrypt the ciphertext.