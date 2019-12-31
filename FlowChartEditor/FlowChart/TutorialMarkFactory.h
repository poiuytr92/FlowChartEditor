#ifndef _TUTORIALMARKFACTORY_H
#define _TUTORIALMARKFACTORY_H

typedef signed long int Long;
class TutorialMark;
class FlowChart;

class TutorialMarkFactory {
public:
	TutorialMarkFactory(FlowChart *sample=0);
	TutorialMarkFactory(const TutorialMarkFactory& source);
	~TutorialMarkFactory();
	TutorialMarkFactory& operator=(const TutorialMarkFactory& source);

	TutorialMark* Make(Long length); //Ʃ�丮�� �ó������� ���� ����(���� � �ó���������)�� ���� ǥ�ø� �޸� ��.
private:
	FlowChart *sample;
};

#endif //_TUTORIALMARKFACTORY_H