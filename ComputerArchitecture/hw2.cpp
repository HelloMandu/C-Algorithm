#include<iostream>
#include<string>
#define SIZE 8
#define MSB 0
using namespace std;

bool Check_Bit(char bit) {//bit�� 0�� �ƴ� �� false, 0�� �� true�� ��ȯ 
	return (bit - '0') ? false : true;
}

void Carry_binary_number(string &binary_number) { // 1�Ǻ��� -> 2�� ����
	int carry = 1; // carry�� �ʱ�ȭ
	for (int i = binary_number.length() - 1; i >= MSB; i--) {
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

string Complement_binary_number(string &binary_number) { // 2������ ������ ����
	string Real_binary_number; // ������ ���� 2����
	for (int i = MSB; i < binary_number.length(); i++) {
		if (Check_Bit(binary_number[i])) // bit�� 0�϶�
				Real_binary_number += '1';
		else // bit�� 1�϶�
				Real_binary_number += '0';
	}
	Carry_binary_number(Real_binary_number);
	return Real_binary_number; // 2�Ǻ��� ���� ���� ��ȯ
}

string Binarization(int num) { // �Է¹��� 10������ 2������ �ٲ�
	bool sign = true; // true = ��� false = ����
	if (num < 0) {
		num *= -1; // num�� ������ �� ������ ����
		sign = false; // ���� ǥ��
	}
	string Binary_number = "00000000"; // ������ 2����
	for (int i = SIZE - 1; i >= MSB; i--) {
		Binary_number[i] = num % 2 + '0';
		num /= 2;
	}
	return sign ? Binary_number : Complement_binary_number(Binary_number); // ����� �׷��� ���, ������ ������ ���
}

void Shift_Left(string &binary_number, int num) { // ���� ����Ʈ
	for (int i = 0; i < num; i++) {
		binary_number += '0';
		binary_number.erase(MSB, 1);
	}
}

void Shift_Right(string &binary_number, int num) { // ������ ����Ʈ
	for (int i = 0; i < num; i++) {
		binary_number = '0' + binary_number;
		binary_number.erase(binary_number.length() - 1, binary_number.length());
	}
}

void Add_binary_number(string &result, string &multiplicand) {
	int carry = 0; // �ʱ��� carry�� 0
	for (int i = SIZE * 2 - 1; i >= MSB; i--) {
		if (result[i] == '0' && multiplicand[i] == '0') { // �Ѵ� 0�� ��
			if (carry) { // carry�� ���� ��
				result[i] = '1';
				carry = 0;
			}
			else // carry�� ���� ��
				result[i] = '0';
		}
		else if (result[i] == '1' && multiplicand[i] == '1') {// �Ѵ� 1�� ��
			if (carry) { // carry�� ���� ��
				result[i] = '1';
				carry = 1;
			}
			else {// carry�� ���� ��
				result[i] = '0';
				carry = 1;
			}
		}
		else { // ���� �ϳ��� 1�� ��
			if (carry) { // carry�� ���� ��
				result[i] = '0';
				carry = 1;
			}
			else // carry�� ���� ��
				result[i] = '1';
		}
	}
}

string Shift_Multiply(int num1, int num2) {
	bool sign = (num1 * num2 > 0) ? true : false; // ���, ����
	string multiplicand, multiplier; // �ǽ¼�, �¼�
	string result = "0000000000000000"; // ������� �� �����κа�
	multiplicand = Binarization(num1); multiplier = Binarization(num2); // �ǽ¼��� �¼��� 2����ȭ
	if (!Check_Bit(multiplicand[MSB]))  // �ǽ¼��� ������ �� ������ ����
		multiplicand = Complement_binary_number(multiplicand);
	if (!Check_Bit(multiplier[MSB])) // �¼��� ������ �� ������ ����
		multiplier = Complement_binary_number(multiplier);
	multiplicand += "00000000"; // �ǽ¼��� 16bit�� ����
	for (int i = SIZE - 1; i >= MSB; i--) { // �¼��� �����ʽ���Ʈ�� �Ͱ� ����
		if (!Check_Bit(multiplier[i])) // ��Ʈ�� 0�ƴ� ��
			Add_binary_number(result, multiplicand); // �������� ����
		Shift_Right(result, 1); // ���������� 1ĭ shift
	}
	return sign ? result : Complement_binary_number(result); // ������ �� ������ ��ȯ
}

int Check_Booth(string &multiplier, int i) {
	if (multiplier[i - 1] == '0') // 0, 1�� ���
		return multiplier[i] == '0' ? 0 : 1;
	else // 2, 3�� ���
		return multiplier[i] == '0' ? 2 : 0;
}

string Booth_Algorithm(int num1, int num2) {
	string multiplicand, multiplier; // �ǽ¼�, �¼�
	string result = "0000000000000000"; // ������� �� �����κа�
	string complement_binary_number;
	multiplicand = Binarization(num1); multiplier = Binarization(num2); // �ǽ¼��� �¼��� 2����ȭ
	multiplier += '0'; // �߰���Ʈ�� �߰�
	if(num1 > 0) // �ǽ¼��� ����� ��
		multiplicand = "00000000" + multiplicand; // �ǽ¼��� 16bit�� ����
	else // �ǽ¼��� ������ ��
		multiplicand = "11111111" + multiplicand; // �ǽ¼��� 16bit�� ����
	for (int i = SIZE; i > MSB; i--) {
		switch (Check_Booth(multiplier, i)) { // Booth�˰��� ����
		case 0: // �ǽ¼��� ���ʽ���Ʈ - 0 0 || 1 1
			Shift_Left(multiplicand, 1);
			break;
		case 1: // �ǽ¼��� �����κа��� ���� �� �ǽ¼��� ���� ����Ʈ - 0 1
			Add_binary_number(result, multiplicand);
			Shift_Left(multiplicand, 1);
			break;
		case 2: // �ǽ¼��� �����κа��� �� �� �ǽ¼��� ���� ����Ʈ - 1 0
			complement_binary_number = Complement_binary_number(multiplicand);
			Add_binary_number(result, complement_binary_number);
			Shift_Left(multiplicand, 1);
			break;
		}
	}
	return result;
}

int main() {
	int multiplicand, multiplier; // �Է¹��� ������ 2��
	while (true) {
		cout << "10���� 2�� �Է�(���� : 128 128) : ";
		cin >> multiplicand >> multiplier;
		if (multiplicand == 128 && multiplier == 128) {
			cout << "���α׷��� �����մϴ�\n";
			break;
		}
		else if (multiplicand > 127 || multiplicand < -127 || multiplier > 127 || multiplier < -127) // ������ ����� ��� Overflow
			cout << "Overflow �߻�\n\n";
		else {
			cout << '\n' << "�����˰���(2) : " << Shift_Multiply(multiplicand, multiplier) << " - 2�� ��������\n\n";
			cout << "Booth �˰��� :  " << Booth_Algorithm(multiplicand, multiplier) << " - 2�� ��������\n\n";
		}
	}
	return 0;
}