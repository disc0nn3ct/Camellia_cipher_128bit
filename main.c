#include <gcrypt.h>
#include <stdio.h>
#include "camellia_128_bit.h"



int main()
{
	printf("Test\n");
	gcry_mpi_t key_1_128 = gcry_mpi_new(0); // 1 test из https://tools.ietf.org/html/rfc3713
	gcry_mpi_t Plaintext_1_128 = gcry_mpi_new(0);
	gcry_mpi_t Ciphertext_1_128 = gcry_mpi_new(0);
	gcry_mpi_scan(&key_1_128, GCRYMPI_FMT_HEX, "0123456789abcdeffedcba9876543210", 0, 0);
	gcry_mpi_scan(&Plaintext_1_128, GCRYMPI_FMT_HEX, "0123456789abcdeffedcba9876543210", 0, 0);
	gcry_mpi_scan(&Ciphertext_1_128, GCRYMPI_FMT_HEX, "67673138549669730857065648eabe43", 0, 0);


	printf("https://tools.ietf.org/html/rfc3713\n");
	gcry_mpi_t a = gcry_mpi_new(0); // 1 test из https://tools.ietf.org/html/rfc3713

	gcry_mpi_t keys_for_round[26];

	round_key(key_1_128, keys_for_round);


	gcry_mpi_t test_chip = gcry_mpi_new(0);

	camellia_encryption(&test_chip, Plaintext_1_128,  keys_for_round);

	printf("Открытый текст: \n");
	gcry_mpi_dump(Plaintext_1_128);
	printf("\n");


	if(gcry_mpi_cmp(Ciphertext_1_128 ,test_chip) == 0 ) // если одинаковые, то тест пройден 
	{
		printf("Test passed\n");

		printf("1 эталон, 2 это что вышло\n");
		gcry_mpi_dump(Ciphertext_1_128);
		printf("\n");
		gcry_mpi_dump(test_chip);
		printf("\n");
	}
	else
	{
		perror("Test failed: ");
	}


	camellia_decryption( &a, test_chip,  keys_for_round);

	if(gcry_mpi_cmp(Plaintext_1_128 ,a) == 0 ) // если одинаковые, то тест пройден 
	{
		printf("Test passed\n");

		printf("Получился начальный тект\n");
		gcry_mpi_dump(a);
		printf("\n");
	}
	else
	{
		perror("Test failed not same: ");
	}




	delete_round_keys(keys_for_round);

	return 0; 
}
