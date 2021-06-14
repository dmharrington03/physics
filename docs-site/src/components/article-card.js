import * as React from "react";

export default function ArticleCard({title, to, imgURL, tag, date}) {
  const format = (
    <div className="uk-card uk-card-default uk-card-hover uk-padding-remove">
      
      <a href={ to } className="card-link">
        <div className="uk-card-media-top">
          <img src={ imgURL } height="auto" data-uk-img/>
          <div class="uk-overlay uk-position-top-right uk-padding-small">
            <span className="uk-label">{ tag }</span>
          </div>
        </div>
        <div className="uk-card-body uk-margin-remove-top uk-text-left">
          <div className="uk-grid-small uk-flex-middle" data-uk-grid="true">
            <div className="uk-width-expand">
              <h3 className="uk-card-title uk-margin-remove">
                { title }
                </h3>
              <p className="uk-text-meta uk-margin-remove-top">
                <time dateTime={ date }>{ date }</time>
              </p>
            </div>
          </div>
        </div>
        <div className="uk-card-footer uk-text-center">
          <a href={ to } className="uk-button uk-button-text">
            Read more
          </a>
        </div>
      </a>

    </div>
  );

  return format;
}
