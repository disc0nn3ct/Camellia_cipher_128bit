#include "camellia_128_bit.h"


void bit_printf(gcry_mpi_t a, unsigned int num_of_bits)
{
	for(unsigned int i=0; i<num_of_bits; i++)
	{
		if(i%4==0 && i != 0)
			printf(" ");
		printf("%d", gcry_mpi_test_bit(a, i));
	}
	printf("\n");
}

void bit_xor(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits)
{
	gcry_mpi_scan(result, GCRYMPI_FMT_HEX, "00", 0, 0);

	// unsigned int lenn;
	// if(gcry_mpi_get_nbits(a) > gcry_mpi_get_nbits(b))
	// {
	// 	lenn = a;
	// }
	// else
	// 	lenn = b;

	for(int i=0; i < num_of_bits; i++)
	{
		if(gcry_mpi_test_bit(a, i) != gcry_mpi_test_bit(b, i))
		{
			gcry_mpi_set_bit(*result, i);
		}
	}

// gcry_mpi_dump(*result);
}

void bit_or(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits) // да 
{
	for(int i=0; i < num_of_bits; i++)
	{
		if(gcry_mpi_test_bit(a, i) == 1 || gcry_mpi_test_bit(b, i) == 1)
		{
			gcry_mpi_set_bit(*result, i);
		}
	}
}

void bit_and(gcry_mpi_t *result,const gcry_mpi_t a,const gcry_mpi_t b,const unsigned int num_of_bits) // да 
{
	for(int i=0; i < num_of_bits; i++)
	{
		if(gcry_mpi_test_bit(a, i) == 1 && gcry_mpi_test_bit(b, i) == 1)
		{
			gcry_mpi_set_bit(*result, i);
		}
	}
}

// битовый сдвиг влево
void bit_lshift(gcry_mpi_t *result, const gcry_mpi_t a, const unsigned int l_bits, const unsigned int num_of_bits)
{
	gcry_mpi_t b = gcry_mpi_new(0);
	b = gcry_mpi_copy(a);
	gcry_mpi_lshift(b, b, l_bits);
	if(gcry_mpi_get_nbits(b) <= num_of_bits)
		*result = gcry_mpi_copy(b);
	else
	{
		gcry_mpi_clear_highbit(b, num_of_bits);
		// bit_printf(a, 12);
		*result = gcry_mpi_copy(b);
	}
	gcry_mpi_release(b);
}

void bit_cyclic_lshift(gcry_mpi_t *result, const unsigned int l_bits, const unsigned int num_of_bits)
{
	gcry_mpi_t a = gcry_mpi_new(0);
	gcry_mpi_t b = gcry_mpi_new(0);
	a = gcry_mpi_copy(*result);
	b = gcry_mpi_copy(*result);


	// printf("old??? \n");
	// bit_printf(*result, num_of_bits);
	// gcry_mpi_lshift(a, a, l_bits); // поменять с обрезкой больше 128 например 
	bit_lshift(&a, a, l_bits, num_of_bits);
	// printf("\na \n");
	// bit_printf(a, num_of_bits);
	
	// printf("\nb \n");
	// bit_printf(b, num_of_bit);
	
	gcry_mpi_rshift(b, b, (num_of_bits - l_bits)); // поменять с обрезкой больше 128 например
	

	// printf("\n bb \n");
	// bit_printf(b, num_of_bits);
	

	bit_or(&a, a, b, num_of_bits);
	*result = gcry_mpi_copy(a);
	// printf("a new \n");
	// bit_printf(a, num_of_bits);

	// printf(" a дап даст ");
	// gcry_mpi_dump(*result);



////////////////////////////////////////////////////

	// *result = a << offset | a >> (32 - offset);
	// gcry_mpi_rshift

	gcry_mpi_release(a);
	gcry_mpi_release(b);
}




void round_key(gcry_mpi_t key)
{
	gcry_mpi_t KL = gcry_mpi_new(0);	
	gcry_mpi_t KR = gcry_mpi_new(0);	
	gcry_mpi_t D1 = gcry_mpi_new(0);	
	gcry_mpi_t D2 = gcry_mpi_new(0);	

	KL = gcry_mpi_copy(key);
	gcry_mpi_scan(&KR, GCRYMPI_FMT_HEX, "00", 0, 0);

	bit_xor(&D1, KL, KR, 128);   // (KL ^ KR)
	gcry_mpi_rshift(D1, D1, 64); // D1 = (KL ^ KR) >> 64	
	printf("\n\nD1 = \n");
	bit_xor(&D2, KL, KR, 128);   // (KL ^ KR)
	bit_and(&D2, D2, MASK64, 128); 	// (KL ^ KR) & MASK64;



	// gcry_mpi_dump(D1);




	gcry_mpi_release(KL);
	gcry_mpi_release(KR);
	gcry_mpi_release(D1);
	gcry_mpi_release(D2);

}

