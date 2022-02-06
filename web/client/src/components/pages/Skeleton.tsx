import React from "react";
import "./Skeleton.css";
import { RouteComponentProps } from "@reach/router";
import { HistoryOutlined, DashboardOutlined } from "@ant-design/icons";
import { useState, useEffect } from "react";
import { get, post } from "../../utilities";

import "antd/dist/antd.css";
import { Slider, Button } from "antd";

type Props = RouteComponentProps;
const Skeleton = (props: Props) => {
  const [speed, setSpeed] = useState<number>(0);

  useEffect(() => {
    get("/api/status").then((res) => setSpeed(res));
  }, []);

  const handleChange = (value) => {
    setSpeed(value);
  };

  const submitSpeed = () => {
    post("/api/input", { speed: speed });
  };

  const stopStirring = () => {
    setSpeed(0);
    post("/api/input", { speed: 0 });
  };
  return (
    <div className="App-container">
      <div className="Slider-container">
        <h3 className="Slider-text"> Stirring Speed </h3>
        <DashboardOutlined className="Slider-icon" />
        <Slider className="Slider-slider" onChange={handleChange} value={speed} />
      </div>
      <Button type="primary" className="Button-large" size="large" onClick={submitSpeed}>
        Submit
      </Button>
      <Button danger
        type="default"
        className="Button-large"
        size="large"
        onClick={stopStirring}
      >
        Stop Stirring
      </Button>
    </div>
  );
};

export default Skeleton;
