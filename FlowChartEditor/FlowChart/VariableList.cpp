#include "VariableList.h"

VariableList::VariableList(Long capacity)
	: variables(capacity) {
	this->capacity = capacity;
	this->length = 0;
	
	//����� �߰��صα�
	this->variables.Store(0, String("AND"));
	this->variables.Store(1, String("EOF"));
	this->variables.Store(2, String("FALSE"));
	this->variables.Store(3, String("NOT"));
	this->variables.Store(4, String("OR"));
	this->variables.Store(5, String("PRINT"));
	this->variables.Store(6, String("READ"));
	this->variables.Store(7, String("START"));
	this->variables.Store(8, String("STOP"));
	this->variables.Store(9, String("TRUE"));
	this->length += 10;
}

VariableList::VariableList(const VariableList& source)
	: variables(source.variables) {
	this->capacity = source.capacity;
	this->length = source.length;
}

VariableList::~VariableList() {

}

VariableList& VariableList::operator=(const VariableList& source) {
	this->variables = source.variables;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long VariableList::Add(String contents) {
	Long i = 0;
	//1. ���� ���ڿ��� ���̸�ŭ �ݺ��Ѵ�.
	while (i < contents.GetLength()) {
		//1.1. ���� ���ڿ����� ���ڸ� �����´�.
		char character = contents.GetAt(i);
		//1.2. �������� ���� �Ǵ� (���� ���ڿ��� ���̰� 1�̻��̰� ������ ����) �ݺ��Ѵ�.
		String variable;
		while ((character >= 65 && character <= 90) || (character >= 97 && character <= 122) ||
			(variable.GetLength() > 0 && (character >= 48 && character <= 57))) {
			//1.2.1. ���� ���ڿ��� �����.
			variable += character;
			//1.2.2. ���� ���ڿ����� ���� ���ڸ� �����´�.
			character = contents.GetAt(++i);
		}
		//1.3. ��������� ������ŭ �׸���, �������ڿ��� �������, ��������� ���纯���� �������ڿ��� ���� ���� ���� �ݺ��Ѵ�.
		Long j = 0;
		while (j < this->length && variable.GetLength() > 0 && this->variables[j] != variable) {
			//(1.3.1. �������ڿ��� ���� ������ �ִ��� ã�´�.)
			j++;
		}
		//1.4. ���� ���ڿ��� ���� ������ ��ã�Ұ�, �������ڿ��� �������, ���� �ƴϸ� ������Ͽ� �߰��Ѵ�.
		if (j >= this->length && variable.GetLength() > 0 && (variable != "READ" && variable != "PRINT")) {
			if (this->length < this->capacity) {
				this->variables.Store(this->length, variable);
			}
			else {
				this->variables.AppendFromRear(variable);
				this->capacity++;
			}
			this->length++;
		}
		i++;
	}

	return this->length;
}

Long VariableList::Find(String contents) {
	//��� : contents �� num �̸� num ���� �����ϴ� �������� �ִ��� Ȯ���Ѵ�.
	Long ret = -1;
	Long i = 0;
	//1. ��������� ������ŭ �׸��� contents�� �����ϴ� �������� ���� ���� �ݺ��Ѵ�.
	while (i < this->length && this->variables[i].FindUntilLength(contents) == -1) {
		//���� �������� contents�� �����ϴ� �������� �ƴϸ� -1 ���
		i++;
	}
	if (i < this->length) {
		ret = i;
	}
	return ret;
}

String& VariableList::GetAt(Long index) {
	return this->variables.GetAt(index);
}