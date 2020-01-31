open Revery;
open Revery.UI;
open Revery.UI.Components;

let init = app => {
  let _ = Revery.Log.listen((_, msg) => print_endline("LOG: " ++ msg));

  let win = App.createWindow(app, "Welcome to tic tac toe!");

  let _ = UI.start(win, <Game />);

  ();
};

App.start(init);
