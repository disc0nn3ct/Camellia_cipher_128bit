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
		else
		{
			gcry_mpi_clear_bit(*result, i);
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

void bit_and(gcry_mpi_t *result, const gcry_mpi_t a, const gcry_mpi_t b, const unsigned int num_of_bits) // да 
{
	for(int i=0; i < num_of_bits; i++)
	{
		
		if( (gcry_mpi_test_bit(a, i) == 1) && (gcry_mpi_test_bit(b, i) == 1))
		{
			// printf("i = %d\n", i);
			gcry_mpi_set_bit(*result, i);
		}
		else
		{
			gcry_mpi_clear_bit(*result, i);
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

void F_camellia(gcry_mpi_t *result, gcry_mpi_t F_IN, gcry_mpi_t KE)
{
if((gcry_mpi_get_nbits(F_IN) > 64) || (gcry_mpi_get_nbits(KE) > 64) )
{
	perror("F_IN or KE to big : ");
}

gcry_mpi_t x;
gcry_mpi_t MASK8;
gcry_mpi_t t[8];
gcry_mpi_t y[8];

x = gcry_mpi_new(64);
MASK8 = gcry_mpi_new(8);
gcry_mpi_scan(&MASK8, GCRYMPI_FMT_HEX, "ff", 0, 0);


for(int i=0; i<8; i++)
{
	t[i] = gcry_mpi_new(8);
	y[i] = gcry_mpi_new(8);
}

bit_xor(&x, F_IN, KE, 64);  // x  = F_IN ^ KE;
gcry_mpi_rshift(t[0], x, 56);   // t1 =  x >> 56;
gcry_mpi_rshift(t[1], x, 48);   // t2 = (x >> 48)
bit_and(&t[1], t[1], MASK8, 8); 	// t2 = (x >> 48) & MASK8;
gcry_mpi_rshift(t[2], x, 40); // t3 = (x >> 40) 
bit_and(&t[2], t[2], MASK8, 8); // t3 = (x >> 40) & MASK8;
gcry_mpi_rshift(t[3], x, 32); // t4 = (x >> 32)
bit_and(&t[3], t[3], MASK8, 8); // t4 = (x >> 32) & MASK8;
gcry_mpi_rshift(t[4], x, 24);  // t5 = (x >> 24)
bit_and(&t[4], t[4], MASK8, 8); // t5 = (x >> 24) & MASK8;
gcry_mpi_rshift(t[5], x, 16); // t6 = (x >> 16)
bit_and(&t[5], t[5], MASK8, 8); // t6 = (x >> 16) & MASK8;
gcry_mpi_rshift(t[6], x, 8); // t7 = (x >>  8)
bit_and(&t[6], t[6], MASK8, 8); // t7 = (x >>  8) & MASK8;
bit_and(&t[7], t[7], MASK8, 8); // t8 =  x & MASK8;







printf("lol \n");
gcry_mpi_dump(t[0]);
printf("\n lol\n");
// gcry_mpi_rshift(t[2], x, 56); 


// t[1] = //


// t[0] =  // t1 = x >> 56








for(int i=0; i<8; i++)
{
	gcry_mpi_release(t[i]);
	gcry_mpi_release(y[i]);
}
gcry_mpi_release(x);
gcry_mpi_release(MASK8);

}






void round_key(gcry_mpi_t key)
{
	// const long long SIGMA[6] =
	// {
	// 	0xA09E667F3BCC908B, 0xB67AE8584CAA73B2, 0xC6EF372FE94F82BE, 0x54FF53A5F1D36F1C, 0x10E527FADE682D1D, 0xB05688C2B3E6C1FD
	// };
	gcry_mpi_t buf1 = gcry_mpi_new(0);	

	gcry_mpi_t KL = gcry_mpi_new(0);	
	gcry_mpi_t KR = gcry_mpi_new(0);	
	gcry_mpi_t D1 = gcry_mpi_new(0);	
	gcry_mpi_t D2 = gcry_mpi_new(0);	
	gcry_mpi_t MASK64 = gcry_mpi_new(0);
	gcry_mpi_t SIGMA[6];

	for(int i=0; i<6; i++)
	{
		SIGMA[i] = gcry_mpi_new(0);
	}

	gcry_mpi_scan(&SIGMA[0], GCRYMPI_FMT_HEX, "A09E667F3BCC908B", 0, 0);
	gcry_mpi_scan(&SIGMA[1], GCRYMPI_FMT_HEX, "B67AE8584CAA73B2", 0, 0);
	gcry_mpi_scan(&SIGMA[2], GCRYMPI_FMT_HEX, "C6EF372FE94F82BE", 0, 0);
	gcry_mpi_scan(&SIGMA[3], GCRYMPI_FMT_HEX, "54FF53A5F1D36F1C", 0, 0);
	gcry_mpi_scan(&SIGMA[4], GCRYMPI_FMT_HEX, "10E527FADE682D1D", 0, 0);
	gcry_mpi_scan(&SIGMA[5], GCRYMPI_FMT_HEX, "B05688C2B3E6C1FD", 0, 0);






	KL = gcry_mpi_copy(key);
	gcry_mpi_scan(&KR, GCRYMPI_FMT_HEX, "00", 0, 0);
	gcry_mpi_scan(&MASK64, GCRYMPI_FMT_HEX, "ffffffffffffffff", 0, 0);



	bit_xor(&D1, KL, KR, 128);   // (KL ^ KR)
	

	gcry_mpi_rshift(D1, D1, 64); // D1 = (KL ^ KR) >> 64	
	


	gcry_mpi_dump(D1);
	printf("\n");

	printf("\n\nD2 = \n");
	bit_xor(&D2, KL, KR, 128);   // (KL ^ KR)
	gcry_mpi_dump(D2);
	printf("\n");
	bit_and(&D2, D2, MASK64, 128); 	// (KL ^ KR) & MASK64;

	F_camellia(&buf1, D1, SIGMA[0]);


	// printf("\n");
	// gcry_mpi_dump(D2);
	// printf("\n");


	// gcry_mpi_dump(D2);




	for(int i=0; i<6; i++)
	{
		gcry_mpi_release(SIGMA[i]);
	}

	gcry_mpi_release(KL);
	gcry_mpi_release(KR);
	gcry_mpi_release(D1);
	gcry_mpi_release(D2);
	gcry_mpi_release(MASK64);

}

