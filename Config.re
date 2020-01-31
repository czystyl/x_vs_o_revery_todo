type player =
  | Cross
  | Circle;

type gameStatus =
  | NotStarted
  | InProgress(player)
  | Finished(player)
  | Draw;

  let possibilities = [
    `FirstRow,
    `SecondRow,
    `ThirdRow,
    `FirstColumn,
    `SecondColumn,
    `ThirdColumn,
    `FirstDiagonal,
    `SecondDiagonal,
  ];
