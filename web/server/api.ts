import express from "express";
import socketManager from "./server-socket";
import twilio from "twilio";
import dotenv from "dotenv";
dotenv.config();

const router = express.Router();

// Twilio SMS
const accountSid = process.env.TWILIO_ACCOUNT_SID;
const authToken = process.env.TWILIO_AUTH_TOKEN;
const twilioClient = twilio(accountSid, authToken);

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
let number = "+16196189435";

// route for handling input from web client
router.post("/input", (req, res) => {
  if (typeof req.body.speed !== "undefined") speed = Number(req.body.speed);
  res.send(speed.toString());
});

// route for handling device polling requests
router.get("/status", (req, res) => {
  res.send(speed.toString());
});

// route for handling device events
router.get("/interrupt", (req, res) => {
  // if (speed === 0) {
  //   res.send("0");
  //   return;
  // }
  speed = 0;
  twilioClient.messages
    .create({
      body: "Your stirrer has finished!",
      from: "+18577631229",
      to: number,
    })
    .then((message) => console.log("Message sent to " + number))
    .catch((err) => console.log(err.message));
  res.send(speed.toString());
});

// anything else falls to this "not found" case
router.all("*", (req, res) => {
  const msg = `Api route not found: ${req.method} ${req.url}`;
  res.status(404).send({ msg });
});

export default router;
