#include<iostream>
#include<string>
#include<math.h>
using namespace std;
#define SIZE 8 // 8bit
#define MSB 0 // ��ȣ��Ʈ

bool Check_Bit(char bit)  {//bit�� 0�� �ƴ� �� false, 0�� �� true�� ��ȯ 
	return (bit - '0') ? false : true;
}

int BinarytoDecimal(string &binary_number, int size) { // 2������ 10������ ���
	int result = 0;
	for (int i = 0; i < size; i++)
		result += (binary_number[SIZE - (i + 1)] - '0') * (int)pow(2, i); // bit * 2^i
	return result;
}

string Complement_binary_number(string &binary_number) { // 2������ ������ ����
	string Real_binary_number; // ������ ���� 2����
	for (int i = 0; i < SIZE; i++) {
		if (Check_Bit(binary_number[i])) // bit�� 0�϶�
			Real_binary_number += '1';
		else // bit�� 1�϶�
			Real_binary_number += '0';
	}
	return Real_binary_number; // ���� ���� ���� ��ȯ
}

void Carry_binary_number(string &binary_number) { // 1�Ǻ��� -> 2�� ����
	int carry = 1; // carry�� �ʱ�ȭ
	for (int i = SIZE - 1; i >= 0; i--) {
		if ((binary_number[i] + carry) - '0' == 2) { // carry�� ���
			binary_number[i] = 0 + '0';
			carry = 1;
		}
		else {  // carry�� �ƴ� ���
			binary_number[i] = (binary_number[i] + carry);
			carry = 0;
			break; // carry�� �����Ƿ� break;
		}
	}
}

int Sign_bit(string &binary_number) { // ��ȣ�� ũ�� ���
	int result;
	result = BinarytoDecimal(binary_number, SIZE - 1); // 2���� -> 10���� ��ȣ��Ʈ�� ����
	return Check_Bit(binary_number[MSB]) ? result : result * -1; // ����� ���
	//��ȣ��Ʈ�� 0�϶� ���, 1�϶� ������ ���
}

int One_Complement(string &binary_number) { // 1�� ���� ���
	int result;
	if (Check_Bit(binary_number[MSB])) // MSB��ȣ�� 0�� ��
		result = BinarytoDecimal(binary_number, SIZE); // 2������ ���
	else { // MSB��ȣ�� 1�� ��
		string Real_binary_number = Complement_binary_number(binary_number); // ������ ���� 2����
		result = BinarytoDecimal(Real_binary_number, SIZE);  // 2���� -> 10����
		result *= -1;  // MSB��ȣ�� 1�̹Ƿ� *-1
	}
	return result; // ����� ���
}

int Two_Complement(string &binary_number) { // 2�� ���� ���
	int result;
	if (Check_Bit(binary_number[MSB])) // MSB��ȣ�� 0�� ��
			result = BinarytoDecimal(binary_number, SIZE); // 2������ ���
	else { // MSB�� 1�� ��
		string Real_binary_number = Complement_binary_number(binary_number); // ������ ���� 2����
		Carry_binary_number(Real_binary_number); // 1�� ���� -> 2�� ����
		result = BinarytoDecimal(Real_binary_number, SIZE); // 2���� -> 10����
		result *= -1; // MSB�� 1�̹Ƿ� ������ ����
	}
	return result; // ����� ���
}

bool Check_binary_number(string &binary_number) { // �Է°��� ����� ���Դ��� Ȯ��
	for (int i = 0; i < SIZE; i++) {
		if (binary_number[i] != '0' && binary_number[i] != '1') // 0 �Ǵ� 1�� �ȵ�� ���� ��
			return false;
	}
	return true; // ���� ����� ��� ���� ��
}

int main() {
	string binary_number; // 8bit����� ������ �迭 ����
	while (true) {
		cout << "2���� ���� �Է����ּ���(����:0) : ";
		cin >> binary_number; // ���� �ϳ��� �Է�
		if (binary_number == "0") { // binary_number 0�� �Է½� ����
			cout << "\n���α׷��� �����մϴ�\n";
			break;
		}
		else if (binary_number.length() != SIZE || !Check_binary_number(binary_number)) // ���� ����� ���Ӵ��� Ȯ��
			cout << "\n8bit 2������ �Է����ּ���.\n\n";
		else { // ���� ����� ��� ���� ��
			cout << "\n2����\n";
			cout << "1) ��ȣ-ũ�� ��� : " << binary_number <<  "\n";
			if (Check_Bit(binary_number[MSB])) { // �Է� ���� ��� �϶�
				cout << "2)  1�� ���� ��� : " << binary_number << "\n";
				cout << "3)  2�� ���� ��� : " << binary_number << "\n\n";
			}
			else { // �Է� ���� ���� �϶�
				cout << "2)  1�� ���� ��� : " << binary_number << "\n";
				string Real_binary_number = Complement_binary_number(binary_number); // 1�� ������ ����
				cout << "   ������ ���� �� : " << Real_binary_number << "\n";
				cout << "3)  2�� ���� ��� : " << binary_number << "\n";
				Carry_binary_number(Real_binary_number); // 1�� ���� + 1
				cout << "   ������ ���� �� : " << Real_binary_number << "\n\n";
			}
			cout << "10����\n";
			cout << "1) ��ȣ-ũ�� ��� : " << Sign_bit(binary_number) << "\n";
			cout << "2)  1�� ���� ��� : " << One_Complement(binary_number) << "\n";
			cout << "3)  2�� ���� ��� : " << Two_Complement(binary_number) << "\n\n";
		}
	}
	return 0;
}