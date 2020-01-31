open Revery.UI;
open Config;

let make = (~sign: player, ()) => {
  let containerStyle = Style.[height(100), width(100)];

  let iconeType =
    switch (sign) {
    | Cross => "cross.png"
    | Circle => "circle.png"
    };

  <Image src=iconeType style=containerStyle />;
};
