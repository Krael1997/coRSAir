/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coRSAir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelrodr <abelrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:12:16 by abelrodr          #+#    #+#             */
/*   Updated: 2023/05/08 15:36:36 by abelrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARYS */

#include <stdlib.h>                   // Standard library  
#include <stdio.h>                   // Standard input/output 
#include <string.h>                 // String library
#include <unistd.h>                // Unix standard library   
#include <fcntl.h>                // File control library   
#include <stdint.h>              // Standard integer library

#include "openssl/bn.h"        // Big number library
#include "openssl/rsa.h"      // RSA library
#include "openssl/pem.h"     // PEM library
#include "openssl/bio.h"    // BIO library
#include "openssl/evp.h"   // EVP library
#include "openssl/x509.h" // X509 library

/* CONSTANT */

#define BUFFER 1024          // Buffer size

/* FUNCTIONS */

RSA *read_public_key(const char *filename)      // Read the public key
{
    // Define variables
    X509 *cert;                         // Certificate X509
    EVP_PKEY *pkey;                     // Public key from the certificate X509
    RSA *rsa;                           // RSA key from the public key
    BIO *bio;                           // BIO to read the file
    int correct;                        // Correctness of the function for check.

    // Initialize variables
    bio = BIO_new(BIO_s_file());        // Initialize BIO
    correct = BIO_read_filename(bio, filename); // Read the filename
    
    // Check if the filename is correct
    if (!correct)
    {
      printf("Error: The file %s cannot be opened.\n", filename);
      exit(1);
    }
    
    // Read the certificate
    cert = PEM_read_bio_X509(bio, NULL, 0, NULL); // Read the certificate
    pkey = X509_get_pubkey(cert);       // Get the public key
    rsa = EVP_PKEY_get1_RSA(pkey);      // Get the RSA key

    // Free memory
    BIO_free(bio);                      // Free the BIO
    X509_free(cert);                    // Free the certificate
    EVP_PKEY_free(pkey);                // Free the public key
    
    // Return the RSA key
    return (rsa);
}

/* MAIN */
int main(int argc, char **argv)       // Main function
{
  // Banner
    printf("\033[31m\n");
    printf("\033[32m                  CREATED BY ABELRODR42                                                                  \033[0m  \n"); 
    printf("\033[31m\n");
    printf("\033[33m                                                               \033[0m\n");
    printf("\033[31m                         ,@@@@@@@@@                     \033[0m\n");
    printf("\033[32m                       @@ \033[33m@@@@@@@@@@#\033[32m                  \033[0m\n");
    printf("\033[31m     @                @ \033[33m@@@@@@@@@@@@\033[31m                @ \033[0m\n");
    printf("\033[32m      @@              @@@   @@,   @ @              @@  \033[0m\n");
    printf("\033[31m       @@@             @   .@ @   @              @@@   \033[0m\n"); 
    printf("\033[32m         @@@@          @@@@@  \033[33m@@@@@@@\033[32m           @@@/    \033[0m\n");
    printf("\033[31m           @@@@         @ \033[33m@@@@@@@\033[31m            @@@@@      \033[0m\n");
    printf("\033[32m             @@@@@      @@       @       @@@@@         \033[0m\n");  
    printf("\033[31m                @@@@@,   \033[33m@@@@@@@\033[31m    &@@@@@.           \033[0m \n");
    printf("\033[32m                   @@@ @@        @@& @@@               \033[0m\n");
    printf("\033[31m            @@@       /@@@ &@@   @@@        @          \033[0m\n");
    printf("\033[32m              %% \033[33m@@@@@@@@   @@@@\033[32m/ @@@@&    @@           \033[0m\n");
    printf("\033[31m       @@@ \033[33m@@@@\033[31m @@ \033[33m@@@@@\033[31m          ,@@@@ (\033[33m@@.@@@@@\033[31m/@@    \033[0m\n");
    printf("\033[32m                @@                      @#     @       \033[0m  \n");  
    printf("\033[31m                                    &                 \033[0m\n");
    printf("\033[32m  \n"); 
    printf("\033[31m  ▄▀▄▄▄▄   ▄▀▀▀▀▄   ▄▀▀▄▀▀▀▄  ▄▀▀▀▀▄  ▄▀▀█▄   ▄▀▀█▀▄     ▄▀▀▄▀▀▀▄ \033[0m\n");
    printf("\033[32m  █ █    ▌ █      █ █   █   █ █ █   ▐ ▐ ▄▀ ▀▄ █   █  █   █   █   █ \033[0m\n");
    printf("\033[31m  ▐ █      █      █ ▐  █▀▀█▀     ▀▄     █▄▄▄█ ▐   █  ▐  ▐  █▀▀█▀   \033[0m\n");  
    printf("\033[32m    █      ▀▄    ▄▀  ▄▀    █  ▀▄   █   ▄▀   █     █      ▄▀    █   \033[0m\n");
    printf("\033[31m   ▄▀▄▄▄▄▀   ▀▀▀▀   █     █    █▀▀▀   █   ▄▀   ▄▀▀▀▀▀▄  █      █      \033[0m\n");
    printf("\033[32m  █     ▐           ▐     ▐    ▐      ▐   ▐   █      █  ▐      ▐     \033[0m\n");
    printf("\033[31m  ▐                                           ▐      ▐               \033[0m\n");


  
    // Define variables
    unsigned char *res;                // Buffer for storage the content of the file encrypted
    unsigned char *sol;                // Buffer for storage the content of the file decrypted
    
    BN_CTX *ctx;                       // Context for the BIGNUM
    RSA *private;                      // Private key
    BIO *bioprint;                     // BIO for print the certificate in the terminal
    BIGNUM *one;                       // One for the BIGNUM
    
    RSA *rsa1;                         // RSA key -----
    BIGNUM *n1;                        // n           - > First certificate
    BIGNUM *q1;                        // q       -----
    
    RSA *rsa2;                         // RSA key -----
    BIGNUM *n2;                        // n           - > Second certificate
    BIGNUM *q2;                        // q       -----

    BIGNUM *p;                         // Prime number, factor of n1 and n2

    BIGNUM *totient;                   // Totient (phi) of n
    BIGNUM *fi1;                       // Totient of n1
    BIGNUM *fi2;                       // Totient of n2

    BIGNUM *e;                         // Exponent of the public key
    BIGNUM *d;                         // Exponent of the private key

    int fd;                            // File descriptor for read the file encrypted
    int len;                           // Length of the file encrypted (number of bytes)

    (void) argc;                       // Unused variable
    
    // Initialize variables and we allocate memory for the variables that need it
    res = malloc(sizeof(unsigned char) * BUFFER); // Allocate memory for the result
    sol = malloc(sizeof(unsigned char) * BUFFER); // Allocate memory for the solution

    ctx = BN_CTX_new();                // Initialize the context
    
    bioprint = BIO_new_fp(stdout, BIO_NOCLOSE); // Initialize the BIO

    // Read the public keys.
    rsa1 = read_public_key(argv[1]);    // Read the public key
    rsa2 = read_public_key(argv[2]);   // Read the public key
    

    // We calculate the prime numbers p, q1 and q2, which are the factors of n1 and n2.
    one = BN_new();                    // Initialize the BIGNUM

    q1 = BN_new();                     // Initialize the BIGNUM
    q2 = BN_new();                     // Initialize the BIGNUM

    p = BN_new();                      // Initialize the BIGNUM
    d = BN_new();                      // Initialize the BIGNUM

    totient = BN_new();
    fi1 = BN_new();
    fi2 = BN_new();

    private = RSA_new();               // Initialize the RSA key

    // Calculate the totient of n1 and n2.
    n1 = (BIGNUM*) RSA_get0_n(rsa1);   // Get the n
    n2 = (BIGNUM*) RSA_get0_n(rsa2);   // Get the n
    e = (BIGNUM*) RSA_get0_e(rsa1);    // Get the e
    
    BN_gcd(p, n1, n2, ctx);           // Calculate the gcd
    BN_div(q1, NULL, n1, p, ctx);     // Calculate the q1
    BN_div(q2, NULL, n2, p, ctx);     // Calculate the q2

    BN_dec2bn(&one, "1");             // Set the one to 1
    BN_sub(fi1, q1, one);             // Calculate the totient of n1
    BN_sub(fi2, p, one);              // Calculate the totient of n2
    BN_mul(totient, fi1, fi2, ctx);     // Calculate the totient
    BN_mod_inverse(d, e, totient, ctx); // Calculate the d

    // Set the private key
    RSA_set0_key(private, n1, e, d);      // Set the private key

    // Asoociate the private key with the RSA key
    RSA_set0_factors(rsa1, p, q1);      // Associate the private key with the RSA key
    RSA_set0_factors(rsa2, p, q2);      // Associate the private key with the RSA key

    // Display the dates of the certificates
    printf("Certificate 1:\n");       // Display the certificate
    RSA_print(bioprint, rsa1, 0);     // Display the certificate
    RSA_print(bioprint, private, 0);    // Display the certificate

    printf("Certificate 2:\n");           // Display the certificate
    RSA_print(bioprint, rsa2, 0);        // Display the certificate
    RSA_print(bioprint, private, 0);    // Display the certificate

    // Read the file and decrypt it
    fd = open(argv[3], O_RDONLY);      // Open the file
    len = read(fd, res, BUFFER);       // Read the file
    RSA_private_decrypt(len, res, sol, private, RSA_PKCS1_PADDING); // Decrypt the file

    // Display the dates of the files
    printf("File encrypted:\n");
    printf("%s\n", res);

    printf("File decrypted:\n");
    printf("%s\n", sol);

    // Free memory
    free(res);                         // Free the result
    free(sol);                         // Free the solution

    BN_CTX_free(ctx);                  // Free the context
    BIO_free(bioprint);                // Free the BIO

    BN_free(one);                      // Free the BIGNUM
    BN_free(n1);                       // Free the BIGNUM
    BN_free(n2);                       // Free the BIGNUM
    BN_free(q1);                       // Free the BIGNUM
    BN_free(q2);                       // Free the BIGNUM
    
    BN_free(p);                        // Free the BIGNUM
    BN_free(d);                        // Free the BIGNUM
    BN_free(e);                        // Free the BIGNUM

    BN_free(totient);                    // Free the BIGNUM
    BN_free(fi1);                      // Free the BIGNUM
    BN_free(fi2);                      // Free the BIGNUM
    
    return 0;
}
