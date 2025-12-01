bool determineRejection(char sensedColor, char pick) {
  bool reject = false;
  if (sensedColor == 'i' && pick == 'w'){
     reject = true;
  } else if (sensedColor == 'd' && pick == 's') {
    reject = true;
  } else if (sensedColor == 'd' && pick == 'w') {
    reject = true;
  } else if (sensedColor == 's' && pick == 's'){
    reject = true;
  }
  return reject;
}
