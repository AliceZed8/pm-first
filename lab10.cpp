#include <iostream>
#include <vector>

class Student
{
private:
	unsigned int m_id;
	std::string m_name;

public:
	Student(int id, std::string name)
	{
		m_id = id;
		m_name = name;
	}

	std::string Name()
	{
		return m_name;
	}
};

class Teacher
{
private:
	unsigned int m_id;
	std::string m_name;
	std::vector<Student*> m_students;

public:
	Teacher(int id, std::string name)
	{
		m_id = id;
		m_name = name;
	}

	void AddStudent(Student*& stud)
	{
        m_patients.push_back(stud);
	}

	void PrintStudent()
	{
		for (size_t i = 0; i < m_students.size(); i++)
			std::cout << m_students[i]->Name() << std::endl;
	}
};

int main()
{

	Teacher* teacher = new Teacher(0, "Pavel");
	teacher->PrintStudent();
	Student* student1 = new Student(1, "Pasha");
	teacher->AddStudent(student1);
	return 0;
}