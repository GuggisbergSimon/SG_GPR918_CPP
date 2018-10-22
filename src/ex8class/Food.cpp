#include <ex8class/Food.h>

Food::Food(Simulation * simulation) :GameObject(simulation) {

}

char Food::GetImage() {
	return 'F';
}