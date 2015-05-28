// Test written to check if PeriodicBC.h
// functions properly

void arrayPeriodicBCTEST()
{
	ArrayPeriodicBC<int,10> array;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			array[i][j]=i+j;
		}
	}

	int numErrors1=0;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if (array[i+10][j+10]!=i+j)
			{
				numErrors1++;
			}
		}
	}


	int numErrors2=0;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if (array[i-10][j-10]!=i+j)
			{
				numErrors2++;
			}
		}
	}


	if ((numErrors1+numErrors2)==0)
	{
		std::cout << "arrayPeriodicBC test PASSED.\n";
	}
	else
	{
		std::cout << "arrayPeriodicBC test FAILED!\n";
	};
}
