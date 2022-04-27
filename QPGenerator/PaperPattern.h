#pragma once
#include "QPGList.h"
#include "QPGPatternSpecification.h" 
#include "QPGQuestion.h"
class PaperPattern
{
private:
	QPGList<QPGPatternSpecification> qPattern;
	QPGList<QPGQuestion>* qBank;//pointer to object of type questionBank createdin quesBank manager

	QPGPatternSpecification* moveToSpecification(int SpecificationId);
	void addSpecification(QPGQuestion* question);
	void setSpecification();
	void listPattern();
	void saveSpecifications(bool setQuestionsOnly);
	void setPaperPattern();
	int sortSpecifications();
	void resetSpecificationNos();


public:
	PaperPattern();
	int manage(QPGList<QPGQuestion>* QuestionBank);
	QPGList<QPGPatternSpecification>* getSpecifications();

};

