open Revery;
open Revery.UI;
open Revery.UI.Components;
open Config;

let make = (~onResetClick, ()) => {
  let winnerTextStyle =
    Style.[
      color(Colors.green),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(32),
    ];

  let resetTextStyle =
    Style.[
      color(Colors.chocolate),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(22),
    ];

  let containerStyle = Style.[alignItems(`Center), justifyContent(`Center)];

  <View style=containerStyle>
    <Text style=winnerTextStyle text="Draw ¯\\_(ツ)_/¯" />
    <Clickable onClick=onResetClick>
      <Text style=resetTextStyle text="Want to play again?" />
    </Clickable>
  </View>;
};
