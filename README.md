# SQL-Database
 C++ SQL imitator using a State Machine

The project is still in works.

The goal is to use a State Machine shown below to process a SQL type statements to create and modify tables. The tables are stores in a B-Tree. 

    // Current State Array Configuration:
    /*===========================================================
     *  | Select | Random Str | * | , | From | Where | And | = |
     * -|--------|------------|---|---|------|-------|-----|---|
     * 0|    1   |     -1     |-1 |-1 |  -1  |  -1   | -1  |-1 |   Check For Starting Commands (e.g. Select Create Drop)
     * -|--------|------------|---|---|------|-------|-----|---|
     * 1|   -1   |      2     | 3 |-1 |  -1  |  -1   | -1  |-1 | Check For * Or Column Name (Add w/e token used in this row to column list/PTree) ---|
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 2|   -1   |     -1     |-1 | 1 |   4  |  -1   | -1  |-1 | If last token was a Column Name check for , or From                                 |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 3|   -1   |     -1     |-1 |-1 |   4  |  -1   | -1  |-1 | If last token was * check for From                                                  |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 4|   -1   |      5     | 6 |-1 |  -1  |  -1   | -1  |-1 | Check For * Or Table Name (Add w/e token used in this row to table list/PTree)      | - Specific Rows Used For Select Command
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |   (Note: More Will Be Needed For Conditionals)
     * 5|   -1   |     -1     |-1 | 4 |  -1  |   7   | -1  |-1 | If last token was a Table Name check for , or Where (Success Row)                   |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 6|   -1   |     -1     |-1 |-1 |  -1  |   7   | -1  |-1 | If last token was * check for Where (Success Row)                                   |
     * -|--------|------------|---|---|------|-------|-----|---|                                                                                     |
     * 7|        |            |   |   |      |       |     |   | Begin Conditional Parsing-----------------------------------------------------------|
     * -|--------|------------|---|---|------|-------|-----|---|
     * 8|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     * 9|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *10|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *11|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     *12|        |            |   |   |      |       |     |   |
     * -|--------|------------|---|---|------|-------|-----|---|
     */
