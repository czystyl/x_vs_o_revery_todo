open Revery;
open Revery.UI;

let make = (~status: Config.gameStatus, ()) => {
  let textStyle =
    Style.[
      color(Colors.whiteSmoke),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(32),
    ];

  <Text
    style=textStyle
    text={
      switch (status) {
      | _ => "TODO: Handle all possieble case and show the correct message for game status"
      }
    }
  />;
};