#include "TutorialController.h"
#include "TutorialForm.h"
#include "FlowChartEditor.h"
#include "Tutorials.h"
#include "TutorialMarkFactory.h"
#include "Expressions.h"
#include "ExpressionFactory.h"

TutorialController::TutorialController(TutorialForm *tutorialForm) {
	this->tutorialForm = tutorialForm;
}

TutorialController::TutorialController(const TutorialController& source) {
	this->tutorialForm = source.tutorialForm;
}

TutorialController::~TutorialController() {

}

TutorialController& TutorialController::operator=(const TutorialController& source) {
	this->tutorialForm = source.tutorialForm;

	return *this;
}

void TutorialController::Update() {
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->tutorialForm->GetParent());
	ExpressionFactory expFactory(editor);
	ScenarioCheckExpression *expression = expFactory.Make(this->tutorialForm->lastConcrete);
	bool ret = expression->Evaluate();
	if (ret == true && this->tutorialForm->main->GetLength() > 0) {
		this->tutorialForm->main->Execute();
		if (this->tutorialForm->lastConcrete != NULL) { //lastConcrete�� �����ϱ� ���� ������� �޸� ���� ����.
			delete this->tutorialForm->lastConcrete;
		}

		this->tutorialForm->lastConcrete = this->tutorialForm->main->Top()->TakeOut();

		if (dynamic_cast<SymbolSelectTutorial*>(this->tutorialForm->lastConcrete) ||
			dynamic_cast<GroupTutorial*>(this->tutorialForm->lastConcrete)) {
			if (this->tutorialForm->current != NULL) { //��� ���� �ó������� ������ �� �ϴ°ǵ�.
				delete this->tutorialForm->current;
			}
			TutorialMarkFactory factory(this->tutorialForm->sample);
			this->tutorialForm->current = factory.Make(this->tutorialForm->main->GetLength());
			this->tutorialForm->Invalidate();
			this->tutorialForm->SetFocus();
		}

		if (this->tutorialForm->main->Top()->GetLength() < 1) {
			Tutorial *current = this->tutorialForm->main->TakeOut();
			if (current != NULL) {
				delete current;
			}
		}
	}
}