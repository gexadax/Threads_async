#include <future>
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

bool make_thread = true;

void quicksort(int* array, long left, long right) {
	if (left >= right) return;
	long left_bound = left;
	long right_bound = right;

	long middle = array[(left_bound + right_bound) / 2];

	do {
		while (array[left_bound] < middle) {
			left_bound++;
		}
		while (array[right_bound] > middle) {
			right_bound--;
		}

		//������ �������� �������
		if (left_bound <= right_bound) {
			std::swap(array[left_bound], array[right_bound]);
			left_bound++;
			right_bound--;
		}
	} while (left_bound <= right_bound);

	if (make_thread && (right_bound - left > 10000))
	{
		// ���� ��������� � ����� ����� ������ ��� 10000
		// �������� ���������� �������� ��� ������ �����
		auto f = async(launch::async, [&]() {
			quicksort(array, left, right_bound);
			});
		quicksort(array, left_bound, right);
	}
	else {
		// ��������� ��� ����� ���������

		quicksort(array, left, right_bound);
		quicksort(array, left_bound, right);
	}
}

int main()
{
	srand(0);
	long arr_size = 100000000;
	int* array = new int[arr_size];
	for (long i = 0; i < arr_size; i++) {
		array[i] = rand() % 500000;
	}

	time_t start, end;


	// ������������� ������
	time(&start);
	quicksort(array, 0, arr_size);
	time(&end);

	double seconds = difftime(end, start);
	printf("The time: %f seconds\n", seconds);

	for (long i = 0; i < arr_size - 1; i++) {
		if (array[i] > array[i + 1]) {
			cout << "Unsorted" << endl;
			break;
		}
	}

	for (long i = 0; i < arr_size; i++) {
		array[i] = rand() % 500000;
	}
	// ������������ ������
	make_thread = false;
	time(&start);
	quicksort(array, 0, arr_size);
	time(&end);
	seconds = difftime(end, start);
	printf("The time: %f seconds\n", seconds);
	delete[] array;
	return 0;
}

