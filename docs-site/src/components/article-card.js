import * as React from "react";

export default function ArticleCard(props) {
  const format = (
    <div
      className="uk-card uk-card-default uk-card-hover 
                            uk-padding-remove"
    >
      <div className="uk-card-media-top">
        <img src="" height="auto" />
      </div>
      <div className="uk-card-body uk-margin-remove-top">
        <div className="uk-grid-small uk-flex-middle" uk-grid="true">
          <div className="uk-width-expand">
            <h3 className="uk-card-title uk-margin-remove">{props.title}</h3>
            <p className="uk-text-meta uk-margin-remove-top">
              <time dateTime="2016-04-01T19:00">April 01, 2016</time>
            </p>
          </div>
        </div>
      </div>
      <div className="uk-card-footer">
        <a href={props.to} className="uk-button uk-button-text">
          Read more
        </a>
      </div>
    </div>
  );

  return format;
}
