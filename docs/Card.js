function ArticleCard (props) {
    const format = (
    <div>
        <div className="uk-card uk-card-default uk-card-hover">
            <div className="uk-card-media-top">
                <img src="img/img0.png" width="auto" height="auto" />
            </div>
            <div className="uk-card-body uk-margin-remove-top">
                <div className="uk-grid-small uk-flex-middle" uk-grid>
                    <div className="uk-width-expand">
                        <h3 className="uk-card-title uk-margin-remove">Kinematics - 1D</h3>
                        <p className="uk-text-meta uk-margin-remove-top"><time datetime="2016-04-01T19:00">April 01, 2016</time></p>
                    </div>
                </div>
            </div>
            <div className="uk-card-footer">
                <a href="#" className="uk-button uk-button-text">Read more</a>
            </div>
        </div>
    </div>);
}

function ArticleList (props) {
    return (
        <div className="uk-container uk-margin-top">
            <div className="uk-grid-column-small uk-grid-row-medium uk-child-width-1-3@s uk-text-center uk-grid-match" uk-grid>
                <ArticleCard />
                <ArticleCard />
                <ArticleCard />
            </div>
        </div>
    );
}

ReactDOM.render(<ArticleList />, document.getElementById('root'));