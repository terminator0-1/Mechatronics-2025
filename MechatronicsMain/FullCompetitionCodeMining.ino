void FullCompetitionCodeMining() {
  // Mining Sequence keeps iron pick
  for (int i = 1; i <= 4; i++) {
    harvestBlockMining('i');

    goToTable();

    dispenceBlockMining(i);

    goToBlockTable(i);
  }
}
