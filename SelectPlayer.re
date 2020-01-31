open Revery;
open Revery.UI;
open Revery.UI.Components;
open Config;

let make = (~onClick: player => unit, ()) => {
  let container = Style.[justifyContent(`Center), flexDirection(`Row)];

  let textStyle =
    Style.[
      color(Colors.whiteSmoke),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(32),
    ];

  <View>
    <Text text="Choose who start the game:" style=textStyle />
    <View
      style=container
      /*
        TODO:
          - Render two <Field /> component with Corss and Circle type
          - handle onClick of <Field /> component and use onClick from props and pass correct sign
       */
    />
  </View>;
};