import express from "express";
import socketManager from "./server-socket";
const router = express.Router();

// router.post("/initsocket", (req, res) => {
//   // do nothing if user not logged in
//   if (req.user) {
//     const socket = socketManager.getSocketFromSocketID(req.body.socketid);
//     if (socket !== undefined) socketManager.addUser(req.user, socket);
//   }
//   res.send({});
// });

// |------------------------------|
// | write your API methods below!|
// |------------------------------|

let speed = 0;

// route for handling input from web client
router.post("/input", (req, res) => {
  if (req.body.speed) speed = req.body.speed;
  res.send(speed.toString());
});

// route for handling device polling requests
router.get("/status", (req, res) => {
  res.send(speed.toString());
});

// route for handling device events
router.post("/interrupt", (req, res) => {
  speed = 0;
  // Handle some event
  res.send(speed.toString());
});

// anything else falls to this "not found" case
router.all("*", (req, res) => {
  const msg = `Api route not found: ${req.method} ${req.url}`;
  res.status(404).send({ msg });
});

export default router;
