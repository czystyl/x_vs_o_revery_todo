open Revery;
open Revery.UI;
open Revery.UI.Components;
open Config;

let%component make = () => {
  let%hook (board, setBoard) = Hooks.state(Board.create());
  let%hook (status, setStatus) = Hooks.state(NotStarted);

  let%hook _ =
    Hooks.effect(
      If((!=), board),
      () => {
        switch (Board.check(~board)) {
        | Some(status) => setStatus(_ => status)
        | None => ()
        };

        None;
      },
    );

  let onClick = (~row: int, ~column: int) => {
    setStatus(status =>
      switch (status) {
      | NotStarted => InProgress(Circle)
      | InProgress(player) =>
        setBoard(board => Board.update(~board, ~row, ~column, ~player));

        InProgress(
          switch (player) {
          | Cross => Circle
          | Circle => Cross
          },
        );
      /* TODO: handle rest cases */
      | _ as status => status
      }
    );
  };

  let onResetClick = () => {
    setBoard(_ => Board.create());
    setStatus(_ => NotStarted);
  };

  let containerStyle =
    Style.[
      position(`Absolute),
      justifyContent(`Center),
      alignItems(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
      backgroundColor(Colors.black),
      alignItems(`Center),
    ];

  <View style=containerStyle>
    {switch (status) {
     | NotStarted =>
       <SelectPlayer
         onClick={player => {setStatus(_ => InProgress(player))}}
       />
     | InProgress(_) => <Board board onClick status />
     | Finished(winner) => <Finished winner onResetClick />
     | Draw => <DrawStatus onResetClick />
     }}
  </View>;
};