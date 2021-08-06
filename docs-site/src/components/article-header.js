import * as React from 'react';

const ArticleHeader = ({imgURL, title}) => {
  const bgStyle = {
    backgroundImage: `linear-gradient(to right, rgba(50, 50, 50, 0), rgba(20, 20, 20, .8)), 
                url('${ imgURL }')`,
    backgroundRepeat: 'no-repeat',
    backgroundAttachment: 'fixed'
  };

  const out = 
  <div>
      <div id="header-bg" 
          className="uk-background-cover uk-background-top-left
          uk-height-large 
          uk-light uk-flex uk-flex-center uk-flex-middle" 
          uk-parallax="bgy: 0, -150;"
          style={ bgStyle }>
          <h1>{ title }</h1> 
      </div>
  </div>;

  return out;
};

export default ArticleHeader;