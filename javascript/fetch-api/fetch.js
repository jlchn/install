function responseInterceptor(response) {
    if (response.status === 401) {
        // return to login page 
    }
    if (response.status === 403) {
        //alert("You don't have permission to perform this action");
    }
    if (!response.ok) {
        var error = new Error(response.statusText);
        error.response = response;
        throw error;
    }
    return response;
}
var originalFetch = window.fetch;
export function fetch (request, init) {
    if (!!init) {
        init.credentials = 'same-origin';
    } else {
        init = {
            credentials: 'same-origin'
        };
    }
    return originalFetch(request, init).then(responseInterceptor);
}
