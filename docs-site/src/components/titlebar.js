import UIkit from "uikit";
import * as React from "react";

export default function TitleBar() {
  return (
    <div>
      <div data-uk-sticky="sel-target: .uk-navbar-container; cls-active: uk-navbar-sticky">
        <nav
          id="nav-bg"
          className="uk-navbar-container uk-light uk-fixed uk-navbar"
          data-uk-navbar
        >
          <div className="uk-navbar-center">
            <a href="/" className="uk-navbar-item uk-logo">
              Computational Physics
            </a>
          </div>
        </nav>
      </div>
      <div
        class="uk-sticky-placeholder"
        style={{ height: "80px", margin: "0px" }}
      ></div>
    </div>
  );
}
