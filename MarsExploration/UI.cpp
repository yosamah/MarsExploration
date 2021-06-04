#include "UI.h"
#include "MarsStation.h"
#include "Formulation.h"
#include "Cancellation.h"
#include "Promotion.h"



UI::UI(MarsStation* Mars)
{
	pMars = Mars;
}

void UI::Read(ifstream& file, Queue<Event>& eventList)  //file.close() //file.eof()
{
	/*The type of each rover*/
	int NumOfPolarRover;
	int NumOfMountRover;
	int NumOfEmergRover;

	/*The speed of each rover*/
	int SpeedOfPolarRover;
	int SpeedOfMountRover;
	int SpeedOfEmergRover;

	/*The number of missions needed before check up*/
	int BeforeCheckup; 

	/*The Check up duration of each rover*/
	int CheckUpDurationPolar;
	int CheckUpDurationMount;
	int CheckUpDurationEmerg;

	/* TODO: For bonus the different speeds add char "B" and check on in to read differently */
	file >> NumOfMountRover >> NumOfPolarRover >> NumOfEmergRover;
	file >> SpeedOfMountRover >> SpeedOfPolarRover >> SpeedOfEmergRover;
	file >> BeforeCheckup;
	file >> CheckUpDurationMount >> CheckUpDurationPolar >> CheckUpDurationEmerg;
	pMars->SetAvailableRovers(NumOfMountRover, NumOfPolarRover, NumOfEmergRover, SpeedOfMountRover, SpeedOfPolarRover, SpeedOfEmergRover, CheckUpDurationMount, CheckUpDurationPolar, CheckUpDurationEmerg, BeforeCheckup);
	
	///////////////////       /////////////////////////
	
	int AutoPromotion;

	int NumOfEvents;

	file >> AutoPromotion;
	pMars->SetAutoPro(AutoPromotion);
	file >> NumOfEvents;
	
	char EventType;


	for (int i = 0; i < NumOfEvents; i++)
	{
		file >> EventType;

		if (EventType == 'F')
		{
			char MissionType;
			int ED, ID, Location, MDUR, Signif;

			file >> MissionType;
			file >> ED >> ID >> Location >> MDUR >> Signif;

			Formulation* F = new Formulation(MissionType,Location,MDUR,Signif,ID,ED);
			eventList.enqueue(F);

		}
		else if (EventType == 'X')
		{
			int ED,ID;
			file >> ED >> ID;
			Cancellation* X =new Cancellation(ID,ED);
			eventList.enqueue(X);
		}
		else if (EventType == 'P')
		{
			int ED, ID;
			file >> ED >> ID;
			Promotion* P = new Promotion(ID, ED);
			eventList.enqueue(P);
		}
	}
}

void UI::InteractiveMode(HashTable<Mission> Mountainous, PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar, int* Arr) 
{
	cout << "Current Day: " << pMars->GetDay() << endl;
	cout << "7ot el number" <<"Wating Missions: "<< "[" << endl;

}