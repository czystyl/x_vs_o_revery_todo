open Revery;
open Revery.UI;
open Revery.UI.Components;

// TODO: use hook componetn here
let make = (~sign: option(Config.player), ~onClick: unit => unit, ()) => {
  // TODO: hover adn setHover should used from Hooks.state
  let hover = false;
  let setHover = _ => ();

  let itemStyle =
    Style.[
      height(120),
      width(120),
      padding(10),
      margin(10),
      border(~color=hover ? Colors.goldenRod : Colors.green, ~width=2),
      backgroundColor(hover ? Colors.grey : Colors.goldenRod),
    ];

  <Clickable onClick>
    <View
      style=itemStyle
      onMouseOver={_ => setHover(_ => true)}
      onMouseOut={_ => setHover(_ => false)}>
      {switch (sign) {
       | _ =>
         <View
           /*
            TODO: if field is not defined show the empty view
                  otherwise show <Mark /> component with correct type
            */
         />
       }}
    </View>
  </Clickable>;
};