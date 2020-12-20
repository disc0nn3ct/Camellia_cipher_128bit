#ifndef CAMELLIA_128_BIT_H  
#define CAMELLIA_128_BIT_H
#include <gcrypt.h>
#include <stdlib.h> // для exit





// gcry_mpi_t camellia_n(gcry_mpi_t text_in, gcry_mpi_t key);

void bit_printf(gcry_mpi_t a, unsigned int num_of_bits);


void bit_xor(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits);


void bit_or(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits); // да 


void bit_and(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits); // да ;


void bit_lshift(gcry_mpi_t *result, const gcry_mpi_t a, const unsigned int l_bits, const unsigned int num_of_bits);


void bit_cyclic_lshift(gcry_mpi_t *result, gcry_mpi_t in,const unsigned int l_bits, const unsigned int num_of_bits);


int Power(int base, int pow);


unsigned int from_mp_to_uint(gcry_mpi_t num); // из 16 ричной в 10 ричную


void SBOX1(gcry_mpi_t *result, gcry_mpi_t num);


void SBOX2(gcry_mpi_t *result, gcry_mpi_t num);


void F_camellia(gcry_mpi_t *result, gcry_mpi_t F_IN, gcry_mpi_t KE);


void round_key(gcry_mpi_t key, gcry_mpi_t end_key[]);


void FL(gcry_mpi_t *result, gcry_mpi_t FL_IN, gcry_mpi_t KE);


void FLINV(gcry_mpi_t *result, gcry_mpi_t FLINV_IN, gcry_mpi_t KE);


void camellia_encryption(gcry_mpi_t *encypted_tex, const gcry_mpi_t M, const gcry_mpi_t subkeys[]);

void camellia_decryption(gcry_mpi_t *text, const gcry_mpi_t M, const gcry_mpi_t subkeys[]);


#endif 

