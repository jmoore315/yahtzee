#include "die.h"
#include <stdlib.h>
//constructor


Die::Die(){
	value = 0;

}
void Die::roll(){
	value = 1 + rand() % 6;
}