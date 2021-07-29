
/* error Summery:
 * Used for returning error codes from any module.
 *
 */

#ifndef SP_ERROR_H
#define SP_ERROR_H


#define FailedOpen do {printf("Failed to open input file"); exit(EXIT_FAILURE);} while(0);
#define FailedRead do {printf("Failed to read from input file");exit(EXIT_FAILURE);} while(0);
#define FailedFseek do {printf("Failed to skip parts of the input file");exit(EXIT_FAILURE);}while(0);
#define DivideByZero do {printf("Division by zero");exit(EXIT_FAILURE);}while(0);
#define FailedWriting do {printf("Falied to write output file"); exit(EXIT_FAILURE);} while(0);
#define MallocFailed do {printf("Malloc Failed"); exit(EXIT_FAILURE);}while(0);
#define ZeroNodes do {printf("Number of nodes can't be zero"); exit(EXIT_FAILURE);}while(0);
#define ZeroEdges do {printf("Number of edges can't be zero"); exit(EXIT_FAILURE);}while(0);
#define InfinityLoop do {printf("Number of iteration bigger than 1500000 * n");exit(EXIT_FAILURE);}while(0);


#endif
