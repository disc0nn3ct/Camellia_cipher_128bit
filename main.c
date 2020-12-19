#include <gcrypt.h>
#include <stdio.h>
#include "camellia_128_bit.h"



int main()
{
	printf("Test 1\n");
	gcry_mpi_t key_1_128 = gcry_mpi_new(0); // 1 test из https://tools.ietf.org/html/rfc3713
	gcry_mpi_t Plaintext_1_128 = gcry_mpi_new(0);
	gcry_mpi_t Ciphertext_1_128 = gcry_mpi_new(0);
	gcry_mpi_scan(&key_1_128, GCRYMPI_FMT_HEX, "0123456789abcdeffedcba9876543210", 0, 0);
	gcry_mpi_scan(&Plaintext_1_128, GCRYMPI_FMT_HEX, "0123456789abcdeffedcba9876543210", 0, 0);
	gcry_mpi_scan(&Ciphertext_1_128, GCRYMPI_FMT_HEX, "67673138549669730857065648eabe43", 0, 0);

	// camellia_n(Plaintext_1_128, key_1_128);


	printf("%d\n", gcry_mpi_get_nbits(Ciphertext_1_128));
	printf("________________________________\n");
	gcry_mpi_t a = gcry_mpi_new(0); // 1 test из https://tools.ietf.org/html/rfc3713
	gcry_mpi_t b = gcry_mpi_new(0);
	gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "fa", 0, 0);
	gcry_mpi_scan(&b, GCRYMPI_FMT_HEX, "aa", 0, 0);

	gcry_mpi_t res = gcry_mpi_new(0); // 1 test из https://tools.ietf.org/html/rfc3713
	// xor_bit(&res , a, b, 8);
	// printf("\nres= \n");
	// gcry_mpi_dump(res);

	// bit_printf(key_1_128, 128);
	// for(int i =0; i < gcry_mpi_get_nbits(a); i++)
	// {
		


	// }


// const long long SIGMA[6] =
// {
// 	0xA09E667F3BCC908B, 0xB67AE8584CAA73B2, 0xC6EF372FE94F82BE, 0x54FF53A5F1D36F1C, 0x10E527FADE682D1D, 0xB05688C2B3E6C1FD
// };

// char SIGMA[6][64];
// strcpy(SIGMA[0], "A09E667F3BCC908B");



// printf("============================%d\n", from_mp_to_uint(a));

// SBOX1(&a, a);

// printf("resuuuuuuu\n");
// gcry_mpi_dump(a);
// printf("\nresuuuuuuu\n");

// SIGMA[0] = "A09E667F3BCC908B";

// printf("SIGMA\n%s\n", SIGMA[0]);




// gcry_mpi_t SIGMA[6];
// SIGMA[0] = gcry_mpi_new(0);


// F_camellia(&res, a, a );














	// cyclic_l_shift(&a, 1, 8);


	// bit_printf(a, 8);
	// bit_printf(b, 8);
	// bit_or(&a, a, b, 8);
	// bit_printf(a, 8);
	// bit_cyclic_lshift(&a, 4, 8);

	// bit_printf(a, 8);
	// bit_printf(a, 8);
	// printf("\n new \n");
	// gcry_mpi_dump(a);


















	round_key(key_1_128);



	return 0; 
}
