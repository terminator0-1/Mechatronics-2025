void FullCompetitionCode(int pickSelect) {
  // Big Switch and main
  // Wait to recieve plans from uno

  // Pick 0 = 'w' --> Crafting Stone
  // Pick 1 = 's' --> Crafting Iron --> Mining Sequence
  
  // 1. Get default start command
  // 2. start harvestBlock sequence --> handles everything to get three stone.
  // 2. start goToTable sequence --> handles getting to the table.
  // 3. start dispenceBlock sequence --> handles everything to drop three blocks in back row.
  // 4. start goToWood sequence --> handles getting over to the pillar
  // 5. start harvestWood sequence --> handles getting two wood.

  // Initialize blocks and picks
  char picks[4] = { 'w', 's', 'i', 'd' };

  char pick = picks[pickSelect];
  
  // Harvest Three Stone
  harvestBlock(pick);

  // Go to Table.
  goToTable();

  // Dispence at Table
  dispenceBlock();

  // Go to Wood.
  goToWood();

  // Harvest Two Wood
  harvestWood(pick);

  // Go the table
  goToTableWood();

  // Dispence Wood
  dispenseWood();

}
