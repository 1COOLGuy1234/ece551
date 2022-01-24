#include "pandemic.h"

void printError(const char *msg){
  fprintf(stderr, "Wrong: %s\n", msg);
  exit(EXIT_FAILURE);
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  char *token_name = NULL;  // record the splitted substring name
  char *token_pop = NULL;   // record the splitted substring population
  token_name = strtok(line, ",");  // use strtok to get substring
  if (token_name == NULL){
    printError("Get name failed!");
  }
  token_pop = strtok(NULL, "\n");
  if (token_pop == NULL){
    printError("Get population failed!");
  }
  // check token_pop (is there any character not from '0' to '9')
  char *pop_pointer = token_pop;
  while (*pop_pointer != '\0') {
    if (*pop_pointer > '9' || *pop_pointer < '0') {
      printError("The population field has character not from 0-9!");
    }
    pop_pointer++;
  }
  // assign ans.name
  int nidx = 0; // index of ans.name
  while(*token_name != '\0'){
    ans.name[nidx++] = *token_name++;
  }
  ans.name[nidx] = '\0';
  // assign ans.population
  uint64_t popu = atol(token_pop);
  if (popu == 0){
    printError("atol function run error!");
  }
  ans.population = popu;
  return ans;
}


void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {  // n_days should be larger than 6
    printError("n_days must larger than 6!");
  }
  unsigned sum = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
      for (size_t j = i; j < i + 7; j++){   // get the mean value
          sum += data[j];
      }
      avg[i] = sum*1.0/7;
      sum = 0;
  }
}


void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  cum[0] = data[0];
  // calculate the accumulation
  for(size_t i = 1; i < n_days; i++){
    cum[i] = cum[i-1] + data[i];
  }
  // times population divide 100000
  for (size_t i = 0; i < n_days; i++){
    cum[i] = cum[i] * 1.0 / pop * 100000; 
  }
}


void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,  // size : n_countries * n_days
                         size_t n_days) {
  //WRITE ME
  unsigned max = 0;  // store the max value
  unsigned idx_country = 0;  // store the corresponding country
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max){
        max = data[i][j];
        idx_country = i;
      }
    }
  }
  char country_name[64];
  strcpy(country_name, countries[idx_country].name);
  unsigned number_cases = max;
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
