import * as React from "react";

const PageFooter = () => {

  return (

    <footer className="uk-height-small uk-flex uk-flex-center 
                  uk-background-secondary uk-flex-column
                  uk-flex-middle uk-light">
      <p>Daniel Harrington</p>
      <ul className="uk-iconnav">
        <li><a href="https://github.com/dmharrington03" 
          data-uk-icon="icon: github-alt; ratio: 1.2"
          target="_blank" rel="noreferrer"></a>
        </li>
      </ul>
    </footer>
  );
};

export default PageFooter;