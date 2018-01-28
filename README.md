## CryptoCipher

• Part 1: Establishment of a shared session key K A,B between the client A and the server B. For this part, we use the Diffie-Hellman key exchange protocol, which is described below:

– Global Public Elements
• q : a sufficiently large prime, such that it is intractable to compute
the discrete logarithms in Z q ∗ .
• α : α < q and α a primitive root of q.

– User A Key Generation
• Select private X_a such that X_a < q
• Calculate public Y A such that Y_a= α ^(X_a) mod q
A → B : {Y_a, q, α}
Here A → B : M denotes party A sends a message M to party B.

– User B Key Generation
• Select private X B such that X B < q
• Calculate public Y B such that Y B = α ^(X_b) mod q
B → A : {Y_b }



– Generation of secret key by User A
• Compute the shared key with B as K A,B = (Y B ) X A mod q

– Generation of secret key by User B
• Compute the shared key with A as K B,A = (Y A ) X B mod q = K A,B


• Part 2: Implementation of Generalized Caesar Cipher using the Established Key in Part 1.

Consider a set of alphabet of definition, which consists of the characters provided:
  = 00 A = 01 K = 11 U = 21 
1 = 31 B = 02 L = 12 V = 22 
2 = 32 C = 03 M = 13 W = 23 
3 = 33 D = 04 N = 14 X = 24 
4 = 34 E = 05 O = 15 Y = 25 
5 = 35 F = 06 P = 16 Z = 26 
6 = 36 G = 07 Q = 17 , = 27 
7 = 37 H = 08 R = 18 . = 28
8 = 38 I = 09 S = 19 ? = 29 
9 = 39 J = 10 T = 20 0 = 30
a = 40 b = 41 c = 41 d = 42 
e = 43 f = 44 g = 45 h = 46
i = 47 j = 48 k = 49 l = 50
m = 51 n = 52 o = 53 p = 54 
q = 55 r = 56 s = 57 t = 58
u = 59 v = 60 w = 61 x = 62 
y = 63 z = 64 ! = 65 

– Alice (client A) encrypts the plaintext, say,
This is 2018!
using a key k = K A,B (mod 66), and sends the ciphertext to Bob (server B). Bob B will decrypt the ciphertext.
– Bob (server B) encrypts the plaintext, say,
Meet me after the party at 10 P.M. night at IIIT felicity ground.
using a key k = K A,B (mod 66), and sends the ciphertext to Alice (client A). A will decrypt the ciphertext.