open Revery;
open Revery.UI;
open Config;

type t = array(array(option(player)));

let create = () => Array.make_matrix(3, 3, None);

let getResult = results => {
  let resultCount =
    results
    |> List.fold_left(
         (count, result) =>
           switch (result) {
           | Some(Cross) => count + 1
           | Some(Circle) => count - 1
           | None => count
           },
         0,
       );

  switch (resultCount) {
  | (-3) => Some(Circle)
  | 3 => Some(Cross)
  | _ => None
  };
};

let getRow = (~board, ~row) => [0, 1, 2] |> List.map(c => board[row][c]);

let getColumn = (~board, ~column) =>
  [0, 1, 2] |> List.map(r => board[r][column]);

let getDiagonal = (~board, ~diag: [< | `FirstDiagonal | `SecondDiagonal]) => {
  switch (diag) {
  | `FirstDiagonal => [0, 1, 2] |> List.map(pos => board[pos][pos])
  | `SecondDiagonal =>
    List.map2((x, y) => board[x][y], [0, 1, 2], [2, 1, 0])
  };
};

let assignResult = (~result: option(player), ~assignTo) => {
  switch (result) {
  | Some(p) => assignTo := Some(Finished(p))
  | None => ()
  };
};

let isBoardFull = (~board) => {
  switch (board) {
  | [|
      [|Some(_), Some(_), Some(_)|],
      [|Some(_), Some(_), Some(_)|],
      [|Some(_), Some(_), Some(_)|],
    |] =>
    true
  | _ => false
  };
};

let hasWinner = (~winner) =>
  switch (winner^) {
  | Some(Finished(_)) => true
  | _ => false
  };

let check = (~board: t) => {
  let break = ref(0);
  let winner = ref(None);

  while (break^ < 8 && !hasWinner(~winner)) {
    switch (List.nth(possibilities, break^)) {
    | `FirstRow =>
      let row = getRow(~board, ~row=0);
      let result = getResult(row);
      assignResult(~result, ~assignTo=winner);
    | `SecondRow =>
      let row = getRow(~board, ~row=1);
      let result = getResult(row);
      assignResult(~result, ~assignTo=winner);
    | `ThirdRow =>
      let row = getRow(~board, ~row=2);
      let result = getResult(row);
      assignResult(~result, ~assignTo=winner);
    | `FirstColumn =>
      let column = getColumn(~board, ~column=0);
      let result = getResult(column);
      assignResult(~result, ~assignTo=winner);
    | `SecondColumn =>
      let column = getColumn(~board, ~column=1);
      let result = getResult(column);
      assignResult(~result, ~assignTo=winner);
    | `ThirdColumn =>
      let column = getColumn(~board, ~column=2);
      let result = getResult(column);
      assignResult(~result, ~assignTo=winner);
    | `FirstDiagonal as diag =>
      let diagonal = getDiagonal(~board, ~diag);
      let result = getResult(diagonal);
      assignResult(~result, ~assignTo=winner);
    | `SecondDiagonal as diag =>
      let diagonal = getDiagonal(~board, ~diag);
      let result = getResult(diagonal);
      assignResult(~result, ~assignTo=winner);
    | exception _ => ()
    };

    break := break^ + 1;
  };

  isBoardFull(~board) && !hasWinner(~winner) ? winner := Some(Draw) : ();

  winner^;
};

let update = (~board: t, ~row: int, ~column: int, ~player: player) => {
  board
  |> Array.mapi((rowIndex, rowField) => {
       switch (rowIndex) {
       | i when i == row =>
         rowField
         |> Array.mapi((i, field) => {
              switch (field) {
              | None when i == column => Some(player)
              | _ as a => a
              }
            })
       | _ => rowField
       }
     });
};

let make = (~board: t, ~status, ~onClick, ()) => {
  let rowStyle = Style.[flexDirection(`Row)];
  let containter = Style.[alignItems(`Center)];

  <View style=containter>
    <GameStatus status />
    {board
     |> Array.mapi((rowIndex, row) => {
          <View style=rowStyle>
            {Array.mapi(
               (columnIndex, column) => {
                 <Field
                   sign=column
                   onClick={_ => {
                     onClick(~row=rowIndex, ~column=columnIndex)
                   }}
                 />
               },
               row,
             )
             |> Array.to_list
             |> React.listToElement}
          </View>
        })
     |> Array.to_list
     |> React.listToElement}
  </View>;
};
